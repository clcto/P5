#include "Shape.h"
#include "Sphere.h"
#include <iostream>

int main( void )
{
   Sphere s;
   /*
   s.Translate( Point( 0, 0, 0) );
   s.Scale( 1, 1, 1 );
   */
   Point p = Point( -10, .5, 0 );
   Vector v = Vector( -1, 0, 0 );
   Ray r = Ray( p, v );

   s.Intersects( r );
}
