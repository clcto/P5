#ifndef RAY_H_
#define RAY_H_

#include "Point.h"
#include "Vector.h"

class Ray
{
   public:
      Ray();
      Ray( const Point&, const Vector& );

   private:
      Point start;
      Vector direction;
};

#endif
