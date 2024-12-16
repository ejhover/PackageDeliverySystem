#include "CoolingDecorator.h"

#include "BeelineStrategy.h"
#include "DataCollection.h"
#include "Drone.h"
#include "IStrategy.h"
#include "Package.h"
#include "SimulationModel.h"

CoolingDecorator::CoolingDecorator(Drone* d) : IEntityDecorator(d) {}

CoolingDecorator::~CoolingDecorator() {
  if (sub) delete sub;
}

void CoolingDecorator::getNextDelivery() { sub->getNextCoolDelivery(); }

Vector3 CoolingDecorator::closestCoolStation() {
  Vector3 closest;
  std::cout << "about to cool. " << std::endl;
  for (Vector3 station : sub->getModel()->coolingStations) {
    if (station.dist(sub->getPosition()) < closest.dist(sub->getPosition()))
      closest = station;
  }
  return closest;
}

bool CoolingDecorator::canGoCool() {
  if (sub->getToPackage()) {  // if you are going to the package
    if ((internalTemp +
         ((sub->getToPackage()->distance() / sub->getSpeed()) / coolingRate)) >
        (32.0 -
         ((sub->getToPackage()->getDestination()).magnitude() /
          sub->getSpeed()) /
             coolingRate)) {  // if the time it will take will make the battery
                              // go under the amount it will take to get from
                              // the destination to a recharge station
      return false;
    }
  } else if (sub->getToFinalDestination()) {
    if ((internalTemp +
         ((sub->getToFinalDestination()->distance() / sub->getSpeed()) /
          coolingRate)) >
        (32.0 - ((sub->getToFinalDestination()->getDestination()).magnitude() /
                 sub->getSpeed()) /
                    coolingRate)) {
      return false;
    }
  }
  return true;
}

void CoolingDecorator::update(double dt) {
  w = w->GetInstance();
  std::string weather = w->getWeather();
  coolingRate = dt;
  if (weather == "Rain") {
    coolingRate = 10.0;
  } else if (weather == "Snow") {
    coolingRate = 1000.0;
  } else if (weather == "Heatwave") {
    coolingRate = 4.0;
  } else if (weather == "Normal") {
    coolingRate = 6.0;
  }
  if (internalTemp >= 32.0) {
    // overheated
  } else if (cooling) {  // at cooling station
    internalTemp -= (dt * 10);
    if (internalTemp <= 0) {
      cooling = false;
      internalTemp = 0;
      sub->notifyObservers(doneCooling);
      DataCollection* d = DataCollection::getInstance();
      d->collectData("Times Cooled", 1);
      if (lastLocation[0] != -9999.0) {
        toLastLocation = new BeelineStrategy(sub->getPosition(), lastLocation);
      }
    }
  } else if (toStation) {  // heading to cool station
    toStation->move(sub, dt);
    internalTemp += dt / coolingRate;
    if (toStation->isCompleted()) {
      sub->notifyObservers(Cooling);
      delete toStation;
      toStation = nullptr;
      cooling = true;
    }
  } else if (toLastLocation) {  // returning to prior location
    toLastLocation->move(sub, dt);
    internalTemp += dt / coolingRate;
    if (toLastLocation->isCompleted()) {
      delete toLastLocation;
      toLastLocation = nullptr;
    }
  } else if (sub->getToPackage() ||
             sub->getToFinalDestination()) {  // has a current destionation
    if (!canGoCool()) {
      lastLocation = sub->getPosition();
      Vector3 closest = closestCoolStation();
      closest[1] = sub->getPosition()[1];
      toStation = new BeelineStrategy(sub->getPosition(), closest);
    } else {
      sub->coolUpdate(dt);
      internalTemp += dt / coolingRate;
    }
  } else {  // no current destination
    internalTemp += dt / coolingRate;
    if (internalTemp >= 23.0) {
      Vector3 closest = closestCoolStation();
      closest[1] = sub->getPosition()[1];
      lastLocation = Vector3(-9999.0);
      toStation = new BeelineStrategy(sub->getPosition(), closest);
    }
    sub->coolUpdate(dt);
  }
}
