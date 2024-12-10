#include "BatteryDecorator.h"

#include "BeelineStrategy.h"
#include "Drone.h"

BatteryDecorator::BatteryDecorator(Drone* d) : IEntityDecorator(d) {}

void BatteryDecorator::getNextDelivery() { sub->getNextDelivery(); }

void BatteryDecorator::update(double dt) {}
