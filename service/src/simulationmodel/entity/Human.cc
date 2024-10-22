#include "Human.h"

Human::Human(const JsonObject& obj) : IEntity(obj) {
  this->destination = {146, 265, -121};
}

Human::~Human() {}

void Human::update(double dt) {
  Vector3 dest1 = {146, 265, -121};
  Vector3 dest2 = {-191, 265, -112};

  if ((this->position - this->destination).magnitude() < 1) {
    // current_destination = !current_destination;
    if (dest2 == destination) {  // moving towards (146,265,-121)
      this->destination = dest1;
    } else {  // moving towards (-191,265,-112)
      this->destination = dest2;
    }
  }

  Vector3 diff = this->destination - this->position;
  Vector3 dir = diff.unit();
  Vector3 move_vec = dir * this->speed * dt;
  this->direction = dir;
  this->position = this->position + move_vec;
}
