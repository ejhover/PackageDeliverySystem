#ifndef RECHARGE_STATION_FACTORY_H_
#define RECHARGE_STATION_FACTORY_H_

#include <vector>

#include "RechargeStation.h"
#include "IEntityFactory.h"

/**
 *@brief Recharge Station Factory to produce Recharge Stations.
 **/
class RechargeStationFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for RechargeStationFactory class.
   **/
  virtual ~RechargeStationFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* createEntity(const JsonObject& entity);
};

#endif
