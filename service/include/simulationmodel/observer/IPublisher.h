#ifndef IPUBLISHER_H_
#define IPUBLISHER_H_

#include <set>
#include <string>

#include "IObserver.h"

/**
 * @class IPublisher
 * @brief Publisher to be realized by other classes.
 **/
class IPublisher {
 public:
  /**
   * @brief adds observer to a list
   * @param o observer to be added
   **/
  virtual void addObserver(const IObserver* o);
  /**
   * @brief removes observer from the list of observers
   * @param o observer to be removed
   **/
  virtual void removeObserver(const IObserver* o);
  /**
   * @brief notifies all observers of the inputed message
   * @param message the message to be sent
   **/
  virtual void notifyObservers(const std::string& message);

 private:
  std::set<const IObserver*> observers;
};

#endif  // IPUBLISHER_H_
