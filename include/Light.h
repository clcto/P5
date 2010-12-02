// --------------------------------------------------------
// Light
//    a light in space that has diffuse and specular
//    RGB Colors
//
// Carick Wienke
// --------------------------------------------------------

#ifndef LIGHT_H_
#define LIGHT_H_

#include "Color.h"

class Light
{
   public:
      float position[3];
      Color diffuse, specular;
};

#endif
