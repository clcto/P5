#include "Ray.h"

/* Instance Variables ----------
      Point start;
      Vector direction;
*/

Ray::Ray()
{
   start.Set( 0, 0, 0 );
   direction.Set( 0, 0, 1 );
}

Ray::Ray( const Point& s, const Vector& d )
{
   start = s;
   direction = d;
   direction.Normalize();
}

const Point& Ray::Start() const
{
   return start;
}

const Vector& Ray::Direction() const
{
   return direction;
}

Point Ray::At( double t ) const
{
   return Point(
      start[X] + t * direction[X],
      start[Y] + t * direction[Y],
      start[Z] + t * direction[Z] );
}
