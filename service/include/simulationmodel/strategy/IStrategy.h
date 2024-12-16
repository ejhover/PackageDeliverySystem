#ifndef I_STRATEGY_H_
#define I_STRATEGY_H_

#include "IEntity.h"

/**
 * @class IStrategy
 * @brief Strategy interface
 */
class IStrategy {
 public:
  virtual ~IStrategy() {}
  /**
   * @brief Move toward next position
   *
   * @param entity Entity to move
   * @param dt Delta Time
   */
  virtual void move(IEntity* entity, double dt) = 0;

  /**
   * @brief Check if the trip is completed
   *
   * @return True if complete, false if not complete
   */
  virtual bool isCompleted() = 0;

  /**
   * @brief Calculates total distance of the current trip
   */
  virtual double distance() = 0;

  /**
   * @brief Returns the destination of the path
   */
  virtual Vector3 getDestination() = 0;
};

#endif
