// --------------------------------------------------------
// Ray
//    a ray of light that has a start location and a
//    unit vector direction
//
// Carick Wienke
// --------------------------------------------------------

#ifndef RAY_H_
#define RAY_H_

#include "Point.h"
#include "Vector.h"

class Ray
{
   public:
      Ray();
      Ray( const Point&, const Vector& );

         // access the start point and direction
      const Point& Start() const;
      const Vector& Direction() const;

      Point At( double t ) const;

   private:
      Point start;
      Vector direction;
};

#endif
