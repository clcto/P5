#include "Shape.h"
#include "Sphere.h"
#include <iostream>

int main( void )
{
   Sphere s;
   Point p = Point( -1.2, 0, 0 );
   Vector v = Vector( 1, -.2, -.1 );
   Ray r = Ray( p, v );

   s.Intersects( r );
}
