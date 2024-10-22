#include "Helicopter.h"

Helicopter::Helicopter(const JsonObject& obj) : IEntity(obj) {
  this->destination = {
      ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400, position.y,
      ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800};
}

Helicopter::~Helicopter() {}

void Helicopter::update(double dt) {
  if ((this->position - this->destination).magnitude() < 1) {
    this->destination = {
        ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400, position.y,
        ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800};
  } else {
    Vector3 diff = this->destination - this->position;
    Vector3 diff_unit = diff.unit();
    this->direction = diff_unit;
    Vector3 movement_vec = diff_unit * this->speed * dt;
    this->position = this->position + movement_vec;
  }
}
