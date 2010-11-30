#ifndef RAY_H_
#define RAY_H_

#include "Point.h"
#include "Vector.h"

class Ray
{
   public:
      Ray();
      Ray( const Point&, const Vector& );

      const Point& Start() const;
      const Vector& Direction() const;

      Point At( double t ) const;

   private:
      Point start;
      Vector direction;
};

#endif
