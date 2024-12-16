#ifndef RED_DECORATOR_H_
#define RED_DECORATOR_H_

#include "PackageColorDecorator.h"

/**
 * @class RedDecorator
 * @brief Allows packages to be colored red.
 **/
class RedDecorator : public PackageColorDecorator {
 public:
  RedDecorator(Package*);
};

#endif  // RED_DECORATOR_H_
