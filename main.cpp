#include "Shape.h"
#include "Sphere.h"
#include <iostream>

int main( void )
{
   Sphere s;
   s.Translate( Point( 0, 0, 0) );
   s.Scale( 3, 2, 1 );
   Point p = Point( -10, 10, 0 );
   Vector v = Vector( 1, -1, 0 );
   Ray r = Ray( p, v );

   s.Intersects( r );
}

