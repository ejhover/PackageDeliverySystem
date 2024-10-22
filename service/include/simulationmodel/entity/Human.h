#ifndef HUMAN_H_
#define HUMAN_H_
#include <cmath>
#include <limits>

#include "Package.h"
#include "math/vector3.h"

/**
 * @class Human
 * @brief Represents a human entity inheriting from IEntity and holds information about the object including 
 *        how it's updated.
 */
class Human : public IEntity {
 public:
  /**
   * @brief Constructor setting initial destination and taking in JsonObject 
   *        which holds details on the object for the website.
   * @param obj JSON object containing the Human's information.
   */
  Human(const JsonObject& obj);

  /**
   * @brief Destructor method for Human object.
   */
  ~Human();

  /**
   * @brief Function updating location and movement of Human object.
   * @param dt Double representing last time since update.
   */
  void update(double dt);

 private:
  Vector3 destination;
};

#endif
