#include "Shape.h"

/* Instance Variables --------------
      Coordinates coord;
      Material material;
*/

Shape::Shape()
{
   Point p = Point( 0, 0, 0 );
   SetTranslation( p );
   SetScale( 1, 1, 1 );
}

Shape::~Shape()
{

}

   // SetTransformation
void Shape::SetTranslation( const Point& p )
{
   location.Set( 0, 0, 0, p[X],
                 0, 0, 0, p[Y],
                 0, 0, 0, p[Z],
                 0, 0, 0, 1 );

   location_inv.Set( 0, 0, 0, -p[X],
                     0, 0, 0, -p[Y],
                     0, 0, 0, -p[Z],
                     0, 0, 0,   1 );
}

void Shape::SetScale( float x, float y, float z )
{
   scale.Set( x, 0, 0, 0,
              0, y, 0, 0,
              0, 0, z, 0,
              0, 0, 0, 1 );

   scale_inv.Set( 1/x, 0,   0,   0,
                  0,   1/y, 0,   0,
                  0,   0,   1/z, 0,
                  0,   0,   0,   1 );
}

   // change how the shape reacts to light
void Shape::SetMaterial( const Material& m )
{
   material = m;
}
