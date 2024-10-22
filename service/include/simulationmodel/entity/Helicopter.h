#ifndef HELICOPTER_H_
#define HELICOPTER_H_
#include <cmath>
#include <limits>

#include "Package.h"
#include "math/vector3.h"

/**
 * @class Helicopter
 * @brief Represents a helicopter entity object holding information(location, movement, etc.) about the helicopter.
 */
class Helicopter : public IEntity {
 public:
  /**
   * @brief Constructor setting initial destination and taking in JsonObject 
   *        which holds details on the object for the website.
   * @param obj JSON object containing the Helicopter's information.
   */
  Helicopter(const JsonObject& obj);

  /**
   * @brief Destructor method for Helicopter object.
   */
  ~Helicopter();

  /**
   * @brief Function updating location and movement of Helicopter object.
   * @param dt Double representing last time since update.
   */
  void update(double dt);

 private:
  Vector3 destination;
};

#endif
