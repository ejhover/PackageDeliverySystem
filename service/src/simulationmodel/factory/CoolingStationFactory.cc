#include "CoolingStationFactory.h"
#include "CoolingStation.h"

IEntity* CoolingStationFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("coolingStation") == 0) {
    std::cout << "CoolingStation Created" << std::endl;
    return new CoolingStation(entity);
  }
  return nullptr;
}
