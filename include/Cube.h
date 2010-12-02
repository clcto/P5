// --------------------------------------------------------
// Cube
//    a shape that represents a cube (or rectangular prism)
//
// Carick Wienke
// --------------------------------------------------------

#ifndef CUBE_H_
#define CUBE_H_

#include "Shape.h"

class Cube : public Shape
{
   public:
         // where does the ray hit the cube
      virtual RayHit* Intersects( const Ray& );
};

#endif
