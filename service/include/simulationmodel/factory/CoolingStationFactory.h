#ifndef COOLINGSTATION_FACTORY_H_
#define COOLINGSTATION_FACTORY_H_

#include <vector>

#include "CoolingStation.h"
#include "IEntityFactory.h"

/**
 * @class CoolingStationFactory
 * @brief cooling station Factory to produce cooling stations class.
 **/
class CoolingStationFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for cooling stations class.
   **/
  virtual ~CoolingStationFactory() {}

  /**
   * @brief Creates cooling station using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* createEntity(const JsonObject& entity);
};

#endif
