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
}
