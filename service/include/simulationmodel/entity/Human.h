#ifndef HUMAN_H_
#define HUMAN_H_

#include "IEntity.h"
#include "IStrategy.h"

/**
 * @class Human
 * @brief Represents a Human in the Simulation. The human walks around the map
 * randomly, like the Helicopter, but cannot fly.
 **/
class Human : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Human(const JsonObject& obj);

  ~Human();

  void update(double dt);

 private:
  static Vector3 kellerPosition;
  IStrategy* movement = nullptr;
  bool atKeller = false;
};

#endif
