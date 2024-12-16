#include "DataCollection.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <fstream>  // Required for std::fstream

DataCollection* DataCollection::datacollector_ = nullptr;

DataCollection::DataCollection() {}

DataCollection::~DataCollection() {
  // csv file
  if (getInstance()) delete getInstance();
}

DataCollection* DataCollection::getInstance() {
  if (datacollector_ == nullptr) {
    datacollector_ = new DataCollection();
  }
  return datacollector_;
}

void DataCollection::collectData(std::string dataName, double dataValue) {
  data[dataName] += dataValue;
}

void DataCollection::createCSV() {
  std::ofstream myFile("simulationData.csv");

  for (auto& [name, data] : data) {
    myFile << name << ", " << data << "\n";
  }
  myFile.close();
}
