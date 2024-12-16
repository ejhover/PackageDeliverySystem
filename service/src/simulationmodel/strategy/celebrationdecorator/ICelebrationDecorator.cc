#include "ICelebrationDecorator.h"

ICelebrationDecorator::ICelebrationDecorator(IStrategy* strategy, double time) {
  this->strategy = strategy;
  this->time = time;
}

ICelebrationDecorator::~ICelebrationDecorator() {
  // Delete dynamically allocated variables
  if (strategy) delete strategy;
}

void ICelebrationDecorator::move(IEntity* entity, double dt) {
  if (!strategy->isCompleted()) {
    strategy->move(entity, dt);
  } else if (!isCompleted()) {
    celebrate(entity, dt);
    time -= dt;
  }
}

bool ICelebrationDecorator::isCompleted() { return time <= 0; }

double ICelebrationDecorator::distance() { return 0.0; }

Vector3 ICelebrationDecorator::getDestination() { return 0.0; }
