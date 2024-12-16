#include "PathStrategy.h"

#include <string>

#include "DataCollection.h"
#include "weather.h"

PathStrategy::PathStrategy(std::vector<Vector3> p) : path(p), index(0) {}

void PathStrategy::move(IEntity* entity, double dt) {
  if (isCompleted()) return;

  Weather* w = Weather::GetInstance();
  std::string weather = w->getWeather();
  double weatherSpeed = 1;
  if (weather == "Rain") {
    weatherSpeed = .8;
  } else if (weather == "Snow") {
    weatherSpeed = .5;
  }

  Vector3 vi = path[index];
  Vector3 dir = (vi - entity->getPosition()).unit();

  entity->setPosition(entity->getPosition() +
                      ((dir * entity->getSpeed() * dt) * weatherSpeed));
  entity->setDirection(dir);

  if (entity->getPosition().dist(vi) < 4) index++;

  DataCollection* d = DataCollection::getInstance();
  d->collectData("Drone Steps Taken", 1);
}

bool PathStrategy::isCompleted() { return index >= path.size(); }

double PathStrategy::distance() {
  double dist = 0.0;
  for (int i = 0; i < path.size() - 1; i++)
    dist += ((path[i + 1] - path[i]).magnitude());
  return dist;
}

Vector3 PathStrategy::getDestination() { return path.back(); }
