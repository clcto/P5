#ifndef RAYHIT_H_
#define RAYHIT_H_

#include "Vector.h"
#include "Point.h"
#include "Shape.h"

class Shape;

class RayHit
{
   public:
      RayHit( const Ray&, double, 
              const Vector&, Shape* );

      double Time() const;
      const Vector& Normal() const;
      const Point& HitPoint() const;
      const Ray& InRay() const;

      Shape* Face() const;

      bool operator==( const RayHit& ) const;

   protected:

      static const double err = 0.1;

      double time;
      Vector normal;
      Ray ray;
      Point hit;
      Shape* shape;

};
#endif
