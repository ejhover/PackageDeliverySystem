#include "weather.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "DataCollection.h"

Weather* Weather::weather_ = nullptr;

Weather::Weather() {
  value = "Normal";
  counter = 0;
}

Weather::~Weather() {}

Weather* Weather::GetInstance() {
  if (weather_ == nullptr) {
    weather_ = new Weather();
  }
  return weather_;
}

void Weather::changeWeather() {
  // std::cout << "test2" << std::endl;
  DataCollection* d = DataCollection::getInstance();
  std::srand(time(0));
  int rand = (std::rand() % 4) + 1;
  if (rand == 1) {
    value = "Normal";
    d->collectData("Number of Normal Weather", 1);
  } else if (rand == 2) {
    value = "Rain";
    d->collectData("Number of Rainstorms", 1);
  } else if (rand == 3) {
    value = "Heatwave";
    d->collectData("Number of Heatwaves", 1);
  } else if (rand == 4) {
    value = "Snow";
    d->collectData("Number of Snowstorms", 1);
  }
  // std::cout << "test3" << std::endl;
  std::string msg = "Weather has changed to " + value;
  notifyObservers(msg);
}

void Weather::update(double dt) {
  // std::cout << counter << std::endl;
  counter += dt;
  if (counter > 15) {
    // std::cout << "test1" << std::endl;
    changeWeather();
    counter = 0;
  }
}
