#ifndef CUBE_H_
#define CUBE_H_

#include "Shape.h"

class Cube : public Shape
{
   public:
      virtual RayHit* Intersects( const Ray& );

   private:
};

#endif
