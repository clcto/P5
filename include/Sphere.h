// --------------------------------------------------------
// Sphere
//    A sphere for ray tracing
//
// Carick Wienke
// --------------------------------------------------------

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Shape.h"

class Sphere : public Shape
{
   public:
      virtual RayHit* Intersects( const Ray& );

   private:
};

#endif
