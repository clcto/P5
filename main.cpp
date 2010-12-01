#include "Shape.h"
#include "Sphere.h"
#include <iostream>

int main( void )
{
   Sphere s;
   s.SetTranslation( Point( 1, 1, 1 ) );
   s.SetScale( 3, 2, 1 );
   Point p = Point( -8, 2, 1 );
   Vector v = Vector( 1, 0, 0 );
   Ray r = Ray( p, v );

   s.Intersects( r );
}
