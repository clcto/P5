#ifndef LIGHT_H_
#define LIGHT_H_

#include "Color.h"

class Light
{
   public:
      float position[3];
      Color ambient, diffuse, specular;
};

#endif
