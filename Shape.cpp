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
   coord.SetTranslation( p );
}

void Shape::SetScale( double x, double y, double z )
{
   coord.SetScale( x, y, z );
}

   // change how the shape reacts to light
void Shape::SetMaterial( const Material& m )
{
   material = m;
}
