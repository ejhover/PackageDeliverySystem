#ifndef RECHARGE_STATION_H
#define RECHARGE_STATION_H

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

class RechargeStation : public IEntity {
 public:
  /**
   * @brief Constructor function to setup recharge station
   * @param obj JSON object containing attributes about the recharge station
   */
  RechargeStation(const JsonObject& obj);

  /**
   * @brief Destructor function
   */
  ~RechargeStation();

  /**
   * @brief Updates the recharge station
   * @param dt difference in time since last update
   */
  void update(double dt);
};
#endif
