#include "SimulationModel.h"

#include "CoolingStationFactory.h"
#include "DroneFactory.h"
#include "HelicopterFactory.h"
#include "HumanFactory.h"
#include "PackageFactory.h"
#include "RechargeStationFactory.h"
#include "RobotFactory.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  entityFactory.addFactory(new DroneFactory());
  entityFactory.addFactory(new PackageFactory());
  entityFactory.addFactory(new RobotFactory());
  entityFactory.addFactory(new HumanFactory());
  entityFactory.addFactory(new HelicopterFactory());
  entityFactory.addFactory(new RechargeStationFactory());
  entityFactory.addFactory(new CoolingStationFactory());
  Weather* w = Weather::GetInstance();
  std::cout << w->getWeather() << std::endl;
  entities.insert(std::pair<int, IEntity*>(w->getId(), w));
  w->addObserver(this);
  // myMap.insert(std::pair<std::string, int>("apple", 5));
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (auto& [id, entity] : entities) {
    delete entity;
  }
  for (auto& [id, cEntity] : cooledEntities) {
    delete cEntity;
  }
  delete graph;
}

IEntity* SimulationModel::createEntity(const JsonObject& entity) {
  std::string name = entity["name"];
  std::string type = entity["type"];
  Vector3 stationPosition;
  JsonArray position = entity["position"];
  bool cool = false;
  if (entity.contains("cooled")) {
    cool = entity["cooled"];
  }

  if (type == "rechargestation") {
    stationPosition = {position[0], 270, position[2]};
    rechargeStations.push_back(stationPosition);
  } else if (type == "coolingStation") {
    stationPosition = {position[0], 270, position[2]};
    coolingStations.push_back(stationPosition);
  }

  std::cout << name << ": " << position << std::endl;
  IEntity* myNewEntity = nullptr;
  if (myNewEntity = entityFactory.createEntity(entity)) {
    // Call AddEntity to add it to the view
    myNewEntity->linkModel(this);
    controller.addEntity(*myNewEntity);
    if (cool) {
      cooledEntities[myNewEntity->getId()] = myNewEntity;
    } else {
      entities[myNewEntity->getId()] = myNewEntity;
    }
    // Add the simulation model as a observer to myNewEntity
    myNewEntity->addObserver(this);
  }

  return myNewEntity;
}

void SimulationModel::removeEntity(int id) { removed.insert(id); }

void SimulationModel::removeCoolEntity(int id) { cooledRemoved.insert(id); }

/// Schedules a Delivery for an object in the scene
void SimulationModel::scheduleTrip(const JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  Robot* receiver = nullptr;

  for (auto& [id, entity] : entities) {
    if (name == entity->getName()) {
      if (Robot* r = dynamic_cast<Robot*>(entity)) {
        if (r->requestedDelivery) {
          receiver = r;
          break;
        }
      }
    }
  }

  Package* package = nullptr;

  for (auto& [id, entity] : entities) {
    if (name + "_package" == entity->getName()) {
      if (Package* p = dynamic_cast<Package*>(entity)) {
        if (p->requiresDelivery()) {
          package = p;
          break;
        }
      }
    }
  }

  if (receiver && package) {
    package->initDelivery(receiver);
    std::string strategyName = details["search"];
    package->setStrategyName(strategyName);
    scheduledDeliveries.push_back(package);
    controller.sendEventToView("DeliveryScheduled", details);
  }
}

void SimulationModel::scheduleCoolTrip(const JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  Robot* receiver = nullptr;

  for (auto& [id, entity] : cooledEntities) {
    if (name == entity->getName()) {
      if (Robot* r = dynamic_cast<Robot*>(entity)) {
        if (r->requestedDelivery) {
          receiver = r;
          break;
        }
      }
    }
  }
  Package* package = nullptr;

  for (auto& [id, entity] : cooledEntities) {
    std::cout << name << "\n";
    std::cout << entity->getName() << "\n";
    if (name + "_package" == entity->getName()) {
      if (Package* p = dynamic_cast<Package*>(entity)) {
        if (p->requiresDelivery()) {
          package = p;
          break;
        }
      }
    }
  }
  if (receiver && package) {
    package->initDelivery(receiver);
    std::string strategyName = details["search"];
    package->setStrategyName(strategyName);
    scheduledCoolDeliveries.push_back(package);
    controller.sendEventToView("DeliveryScheduled", details);
  }
}

const routing::Graph* SimulationModel::getGraph() const { return graph; }

void SimulationModel::setGraph(const routing::Graph* graph) {
  if (this->graph) delete this->graph;
  this->graph = graph;
}

/// Updates the simulation
void SimulationModel::update(double dt) {
  for (auto& [id, entity] : entities) {
    entity->update(dt);
    controller.updateEntity(*entity);
  }

  for (auto& [cId, cEntity] : cooledEntities) {
    cEntity->update(dt);
    controller.updateEntity(*cEntity);
  }

  for (int id : removed) {
    removeFromSim(id);
  }

  for (int cId : cooledRemoved) {
    removeCoolFromSim(cId);
  }

  removed.clear();
  cooledRemoved.clear();
}

void SimulationModel::stop(void) {}

void SimulationModel::removeFromSim(int id) {
  IEntity* entity = entities[id];

  if (entity) {
    for (auto i = scheduledDeliveries.begin(); i != scheduledDeliveries.end();
         ++i) {
      if (*i == entity) {
        scheduledDeliveries.erase(i);
        break;
      }
    }

    controller.removeEntity(*entity);

    entities.erase(id);

    delete entity;
  }
}

void SimulationModel::removeCoolFromSim(int id) {
  IEntity* entity = cooledEntities[id];

  if (entity) {
    for (auto i = scheduledCoolDeliveries.begin();
         i != scheduledCoolDeliveries.end(); ++i) {
      if (*i == entity) {
        scheduledCoolDeliveries.erase(i);
        break;
      }
    }

    controller.removeCoolEntity(*entity);

    cooledEntities.erase(id);

    delete entity;
  }
}

void SimulationModel::notify(const std::string& message) const {
  JsonObject details;
  details["message"] = message;
  this->controller.sendEventToView("Notification", details);
}

// In write upm say different strategies for cooled and
// regulr would make more sense, but client (shonal) said not to refactor
