#include "BatteryDecorator.h"

#include "DataCollection.h"

BatteryDecorator::BatteryDecorator(Drone* d) : IEntityDecorator(d) {}

BatteryDecorator::~BatteryDecorator() {
  if (toStation) delete toStation;
  if (toLastLocation) delete toLastLocation;
  if (sub) delete sub;
}

void BatteryDecorator::getNextDelivery() { sub->getNextDelivery(); }

Vector3 BatteryDecorator::closestStation() {
  Vector3 closest;
  for (Vector3 station : sub->getModel()->rechargeStations) {
    if (station.dist(sub->getPosition()) < closest.dist(sub->getPosition()))
      closest = station;
  }
  return closest;
}

bool BatteryDecorator::canGo() {
  Vector3 closest = closestStation();
  if (sub->getToPackage()) {  // if you are going to the package
    if ((batteryLevel - ((sub->getToPackage()->distance() / sub->getSpeed()) /
                         depletionRate)) <
        (((sub->getToPackage()->getDestination() - closest).magnitude() /
          sub->getSpeed()) /
         depletionRate)) {  // if the time it will take will make the battery go
                            // under the amount it will take to get from the
                            // destination to a recharge station
      return false;
    }
  } else if (sub->getToFinalDestination()) {
    if ((batteryLevel -
         ((sub->getToFinalDestination()->distance() / sub->getSpeed()) /
          depletionRate)) <
        (((sub->getToFinalDestination()->getDestination() - closest)
              .magnitude() /
          sub->getSpeed()) /
         depletionRate)) {
      return false;
    }
  }
  return true;
}

void BatteryDecorator::update(double dt) {
  if (batteryLevel <= 0) {
    // dead battery. Do nothing
  } else if (charging) {  // at a recharge station
    batteryLevel += (dt * 20);
    if (batteryLevel >=
        100.0) {  // finished charging. Head back to dropped package
      charging = false;
      batteryLevel = 100.0;
      sub->notifyObservers(doneCharging);
      DataCollection* d = DataCollection::getInstance();
      d->collectData("Times Charged", 1);
      if (lastLocation[0] != -9999.0) {
        toLastLocation = new BeelineStrategy(sub->getPosition(), lastLocation);
      }
    }
  } else if (toStation) {  // heading to recharge station
    toStation->move(sub, dt);
    batteryLevel -= dt / depletionRate;
    DataCollection* d = DataCollection::getInstance();
    d->collectData("Battery Power Expended", (dt / depletionRate));
    if (toStation->isCompleted()) {  // made it to recharge station
      sub->notifyObservers(recharging);
      delete toStation;
      toStation = nullptr;
      charging = true;
    }
  } else if (toLastLocation) {  // go back to location before charging. Now with
                                // full battery, shouldn't have to check if we
                                // can make it to our last location
    toLastLocation->move(sub, dt);
    batteryLevel -= dt / depletionRate;
    DataCollection* d = DataCollection::getInstance();
    d->collectData("Battery Power Expended", (dt / depletionRate));
    if (toLastLocation->isCompleted()) {  // made it to the dropped package
      delete toLastLocation;
      toLastLocation = nullptr;
    }
  } else if (sub->getToPackage() ||
             sub->getToFinalDestination()) {  // has a current destination
                                              // (package or final destination)
    if (!canGo()) {  // it can't make it to the destination with enough battery
                     // left to make it to a recharge station
      lastLocation = sub->getPosition();
      Vector3 closest = closestStation();
      closest[1] = sub->getPosition()[1];
      toStation = new BeelineStrategy(sub->getPosition(), closest);
    } else {  // it can make it to the destination
      sub->update(dt);
      batteryLevel -= (dt / depletionRate);
      DataCollection* d = DataCollection::getInstance();
      d->collectData("Battery Power Expended", (dt / depletionRate));
    }
  } else {  // doesn't have a current destination
    batteryLevel -= (dt / depletionRate);
    DataCollection* d = DataCollection::getInstance();
    d->collectData("Battery Power Expended", (dt / depletionRate));
    if (batteryLevel <= 21) {
      Vector3 closest = closestStation();
      closest[1] = sub->getPosition()[1];
      lastLocation = Vector3(-9999.0);
      toStation = new BeelineStrategy(sub->getPosition(), closest);
    }
    sub->update(dt);
  }
}
