#include "SpinDecorator.h"

SpinDecorator::SpinDecorator(IStrategy* strategy, double time, double spinSpeed)
    : ICelebrationDecorator(strategy, time), spinSpeed(spinSpeed) {}

void SpinDecorator::celebrate(IEntity* entity, double dt) {
  entity->rotate(dt * entity->getSpeed() * spinSpeed);
}

double SpinDecorator::distance() {
  if (strategy) {
    return strategy->distance();
  } else {
    return 0.0;
  }
}

Vector3 SpinDecorator::getDestination() {
  if (strategy) {
    return strategy->getDestination();
  } else {
    return Vector3(0);
  }
}
