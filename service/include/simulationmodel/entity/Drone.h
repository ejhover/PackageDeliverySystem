#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

class Package;

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(const JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();

  /**
   * @brief Gets the next delivery in the scheduler
   */
  void getNextDelivery();

  /**
   * @brief gets the next delivery for cool drones
   */
  void getNextCoolDelivery();
  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   */
  void update(double dt);

  /**
   * @brief Updates cool drones' position
   * @param dt Delta time
   */
  void coolUpdate(double dt);

  /**
   * @brief Returns the IStrategy pointer to travel to the package
   */
  IStrategy* getToPackage();

  /**
   * @brief Returns the IStrategy pointer to bring the package to the final destination
   */
  IStrategy* getToFinalDestination();

  /**
   * @brief Removing the copy constructor operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;

  /**
   * @brief Removing the assignment operator
   * so that drones cannot be copied.
   */
  Drone& operator=(const Drone& drone) = delete;

  /**
   * @brief returns false if the drone is not a cooling drone
   */
  virtual bool canPickUpCooledPackages() { return false; }

 private:
  bool available = false;
  bool pickedUp = false;
  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  IStrategy* toFinalDestination = nullptr;
};

#endif
