#ifndef COOLING_STATION_H_
#define COOLING_STATION_H_

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

/**
 * @class CoolingStation
 * @brief Cooling Station entity where cooled entities can go to cool their packages.
 */
class CoolingStation : public IEntity {
 public:
  /**
   * @brief coolingstations are created with default locations
   * @param obj JSON object containing the cooling stations information
   */
  CoolingStation(const JsonObject& obj);
    /**
   * @brief Ccooling station destructor
   */
  ~CoolingStation();

  /**
   * @brief Updates the cooling station
   * @param dt difference in time since last update
   */
  void update(double dt);
};

#endif
