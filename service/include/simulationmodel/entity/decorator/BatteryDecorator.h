#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "Drone.h"
#include "IEntityDecorator.h"

/**
 * @class BatteryDecorator
 * @brief Decorator class to add battery attributes to the Drones.
 */
class BatteryDecorator : public IEntityDecorator<Drone> {
 public:
  /**
   * @brief Battery constructor to set the sub to drone
   * @param d Drone pointer which gets set the sub. The drone being decorated.
   */
  BatteryDecorator(Drone* d);
  /**
   * @brief Gets the next delivery in the scheduler.
   */
  void getNextDelivery();
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  void update(double dt);
  /**
   * @brief Removing the copy constructor operator
   * so that drones cannot be copied.
   */
  BatteryDecorator(const BatteryDecorator& bd) = delete;

  /**
   * @brief Removing the assignment operator
   * so that drones cannot be copied.
   */
  BatteryDecorator& operator=(const BatteryDecorator& bd) = delete;

 private:
  int batteryLevel = 100;
  int maxCapacity = 100;
  bool charging = false;
  Drone* drone = nullptr;
};

#endif