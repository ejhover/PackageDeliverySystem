#ifndef BLUE_DECORATOR_H_
#define BLUE_DECORATOR_H_

#include "PackageColorDecorator.h"

/**
 * @class BlueDecorator
 * @brief Allows packages to be colored blue, but is limited to cooled packages.
 **/
class BlueDecorator : public PackageColorDecorator {
 public:
  BlueDecorator(Package*);
};

#endif  // BLUE_DECORATOR_H_
