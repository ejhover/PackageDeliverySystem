#ifndef COOLING_DECORATOR_H_
#define COOLING_DECORATOR_H_

#include "Drone.h"
#include "IEntityDecorator.h"
#include "weather.h"
#include "SimulationModel.h"
#include "BeelineStrategy.h"

/**
 * @class CoolingDecorator
 * @brief Decorator class to add cooling attributes to the Drones.
 */
class CoolingDecorator : public IEntityDecorator<Drone> {
 public:
  /**
   * @brief Cooling constructor to add the cooling system to the drone.
   * @param drone The drone to be decorated.
   */
  CoolingDecorator(Drone* drone);

  /**
   * @brief Destructor forCooling Decorator
   */
  ~CoolingDecorator();
  /**
   * @brief Gets the next delivery in the scheduler.
   */
  void getNextDelivery();
  /**
   * @brief updates the cooling drone in the simulation.
   * @param dt update increment for the simulation.
   */
  void update(double dt);
  /**
   * @brief Removing the copy constructor operator
   */
  CoolingDecorator(const CoolingDecorator& bd) = delete;

  /**
   * @brief Returns the location of the closest cooling station
   */
  Vector3 closestCoolStation();

  /**
   * @brief Removing the assignment operator
   */
  CoolingDecorator& operator=(const CoolingDecorator& bd) = delete;

  /**
   * @brief returns true if a drone is in a cooling wrapper
   */
  bool canPickUpCooledPackages() override {return true; }

 private:
  bool canGoCool();
  bool cooling = false;
  Weather* w;
  double coolingRate;
  double internalTemp = 0;
  Vector3 lastLocation;
  IStrategy* toStation = nullptr;
  IStrategy* toLastLocation = nullptr;
  std::vector<Vector3> CoolingStations = {
      {-650.92077829579989, 250, -220.91667955813006},
      {720.27673284375555, 250, 240.63121772544486},
      {-470.11371303979422, 250, 425.09544462928},
      {184.262223523297, 250, -325.00871856575702}};
  std::string doneCooling = sub->getName() + " is done cooling.";
  std::string Cooling = sub->getName() + " is now cooling.";
};

#endif
