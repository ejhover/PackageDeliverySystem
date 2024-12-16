#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "BeelineStrategy.h"
#include "Drone.h"
#include "IEntityDecorator.h"
#include "SimulationModel.h"

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
   * @brief Destructor for Battery Decorator
   */
  ~BatteryDecorator();
  /**
   * @brief Gets the next delivery in the scheduler.
   */
  void getNextDelivery();

  /**
   * @brief Returns the location of the closest recharge station
   */
  Vector3 closestStation();
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
  bool canGo();
  double batteryLevel = 100.0;
  bool charging = false;
  double depletionRate =
      1.8;  // the higher the number, the slower the battery depletes
  Vector3 lastLocation;
  IStrategy* toStation = nullptr;
  IStrategy* toLastLocation = nullptr;
  std::vector<Vector3> rechargeStations = {
      {-653.92077829579989, 270, -243.91667955813006},
      {-472.11371303979422, 270, 447.09544462928},
      {723.27673284375555, 270, 262.63121772544486},
      {189.262223523297, 270, -354.00871856575702}};
  std::string doneCharging = sub->getName() + " is done recharging.";
  std::string recharging = sub->getName() + " is now recharging.";
};

#endif
