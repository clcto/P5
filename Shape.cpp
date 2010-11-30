#include "Shape.h"

/* Instance Variables --------------
Matrix location;
Matrix scale;

Matrix location_inv;
Matrix scale_inv;

Material material;
*/

Shape::Shape()
{
   location.Set( 0, 0, 0, 0,
                 0, 0, 0, 0,
                 0, 0, 0, 0,
                 0, 0, 0, 1 );
}

Shape::~Shape()
{

}

   // SetTransformation
void Shape::SetTranslation( Point p )
{

}

void Shape::SetScale( float x, float y, float z )
{

}

   // change how the shape reacts to light
void Shape::SetMaterial( Material m )
{

}
