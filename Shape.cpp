// --------------------------------------------------------
// Shape
//    A shape in space that allows for ray tracing through
//    finding the intesection of a ray with it
//
// Carick Wienke
// --------------------------------------------------------

#include "Shape.h"

   // translate the shape
void Shape::Translate( const Point& p )
{
   coord.Translate( p );
}

   // translate the shape
void Shape::Translate( float x, float y, float z )
{
   coord.Translate( Point( x, y, z ) );
}

   // scale the shape
void Shape::Scale( float x, float y, float z )
{
   coord.Scale( x, y, z );
}

   // change how the shape reacts to light
void Shape::SetMaterial( const Material& m )
{
   material = m;
}

   // get the material
Material Shape::GetMaterial() const
{
   return material;
}
