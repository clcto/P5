#include "Shape.h"

/* Instance Variables --------------
      Coordinates coord;
      Material material;
*/

   // SetTransformation
void Shape::Translate( const Point& p )
{
   coord.Translate( p );
}

void Shape::Scale( float x, float y, float z )
{
   coord.Scale( x, y, z );
}

   // change how the shape reacts to light
void Shape::SetMaterial( const Material& m )
{
   material = m;
}

Material Shape::GetMaterial() const
{
   return material;
}
