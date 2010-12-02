// --------------------------------------------------------
// Ray
//    a ray of light that has a start location and a
//    unit vector direction
//
// Carick Wienke
// --------------------------------------------------------

#include "Ray.h"

   // create a default ray
Ray::Ray()
{
   start.Set( 0, 0, 0 );
   direction.Set( 0, 0, 1 );
}

   // create a ray starting at s in direction d
Ray::Ray( const Point& s, const Vector& d )
{
   start = s;
   direction = d;
   direction.Normalize();
}

   // return the start point
const Point& Ray::Start() const
{
   return start;
}

   // return the direction
const Vector& Ray::Direction() const
{
   return direction;
}

   // return the position at 't' from the start
   // down the direction of the ray
Point Ray::At( double t ) const
{
   return Point(
      start[X] + t * direction[X],
      start[Y] + t * direction[Y],
      start[Z] + t * direction[Z] );
}
