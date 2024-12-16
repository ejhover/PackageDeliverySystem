#ifndef WEATHER_H_
#define WEATHER_H_

#include <string>

#include "IEntity.h"
#include "IPublisher.h"

/**
 * @class Weather
 * @brief Weather Singleton handles the swapping of weather conditions during
 * the simulation.
 **/
class Weather : public IEntity {
 protected:
  /**
   * @brief Default Constructor for Weather, only called during GetInstance.
   * Also sets weather to 'Normal' as default.
   **/
  Weather();
  /**
   * @brief Destructor that will delete the wearther singleton
   **/
  ~Weather();

  static Weather* weather_;

  std::string value;

  double counter;

 public:
  /**
   * @brief Prevents Weather from being duplicated, preserving only one
   *instance.
   **/
  Weather(Weather& other) = delete;

  /**
   * @brief Prevents the equal operator being used on Weather, preserving
   * only one instance.
   **/
  void operator=(const Weather&) = delete;

  /**
   * @brief Creates Singleton if none exists yet, then returns pointer to the
   * existing Singleton.
   **/
  static Weather* GetInstance();

  /**
   * @brief Changes weather using a random number, can swap to either Normal,
   * Heatwave, Rain, or Snow.
   **/
  void changeWeather();

  /**
   * @brief Returns the weather name that is changed by changeWeather, or set
   * by the default constructor.
   **/
  std::string getWeather() { return value; }

  /**
   * @brief Overrides IEntity's 'update' function to be able to keep track
   * of how much time is passing in the simulation. Time is used to track
   * when to change weather.
   * @param dt Delta time.
   **/
  void update(double dt);
};

#endif
