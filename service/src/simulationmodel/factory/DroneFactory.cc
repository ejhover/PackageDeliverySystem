#include "DroneFactory.h"
#include "BatteryDecorator.h"
#include "CoolingDecorator.h"

IEntity* DroneFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("drone") == 0) {
    std::cout << "Drone Created" << std::endl;
    return (new BatteryDecorator(new Drone(entity)));
  }
  if (type.compare("coolDrone") == 0) {
    std::cout << "Cool Drone Created" << std::endl;
    return (new BatteryDecorator(new CoolingDecorator(new Drone(entity))));
  }
  return nullptr;
}

