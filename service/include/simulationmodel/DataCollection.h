#ifndef DATACOLLECT_H_
#define DATACOLLECT_H_

#include <map>
#include <string>

#include "IPublisher.h"

/**
 * @class DataCollection
 * @brief DataCollection Singleton handles collection of various data values
 * over the course of the simulation, and writes the data to a csv file upon
 * destruction.
 **/
class DataCollection {
 protected:
  /**
   * @brief Default Constructor for DataCollection, only called during
   *GetInstance.
   **/
  DataCollection();

  /**
   * @brief Destructor that will delete data collection singleton.
   **/
  ~DataCollection();

  static DataCollection* datacollector_;

  std::map<std::string, double> data;

  std::string dataName;

  double dataValue;

 public:
  /**
   * @brief Prevents DataCollection from being duplicated, preserving only one
   *instance.
   **/
  DataCollection(DataCollection& other) = delete;

  /**
   * @brief Prevents the equal operator being used on DataCollection, preserving
   * only one instance.
   **/
  void operator=(const DataCollection&) = delete;

  /**
   * @brief Creates Singleton if none exists yet, then returns pointer to the
   * existing Singleton.
   **/
  static DataCollection* getInstance();

  /**
   * @brief Collects data into a map to be later written to a csv file.
   * @param dataName The name of the data being logged.
   * @param dataValue The value of the data being logged.
   **/
  void collectData(std::string dataName, double dataValue);

  /**
   * @brief Writes CSV file from the data map
   **/
  void createCSV();
};

#endif
