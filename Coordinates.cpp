// --------------------------------------------------------
// Coordinates
//    class that represents a coordinate system
//    (for an object). It allows for transforming
//    between the world and object coordinates
//
// Carick Wienke
// --------------------------------------------------------

#include "Coordinates.h"

   // create coordinates with no translate or scale
Coordinates::Coordinates()
{
   trans.Set(
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1 );

   inv_trans.Set(
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1 );
}

   // scale the system by the parameters passed
void Coordinates::Scale( double x, double y, double z )
{
   trans = trans * Matrix( x, 0, 0, 0,
                           0, y, 0, 0,
                           0, 0, z, 0,
                           0, 0, 0, 1 );
   inv_trans = Matrix( 1/x, 0, 0, 0,
                       0, 1/y, 0, 0,
                       0, 0, 1/z, 0,
                       0, 0, 0, 1 ) * inv_trans;
}

   // translate the coordinates
void Coordinates::Translate( const Point& p )
{
   trans = trans * Matrix( 1, 0, 0, p[X],
                           0, 1, 0, p[Y],
                           0, 0, 1, p[Z],
                           0, 0, 0,    1 );
   inv_trans = Matrix( 1, 0, 0, -p[X],
                       0, 1, 0, -p[Y],
                       0, 0, 1, -p[Z],
                       0, 0, 0,    1 ) * inv_trans;
}

   // converts the vector to world coordinate
Vector Coordinates::ToWorld( const Vector& v )
{
   return trans*v;
}

   // converts the point to world coordinates
Point Coordinates::ToWorld( const Point& p )
{
   return trans*p;
}

   // coverts the vector to object coordinates
Vector Coordinates::ToObject( const Vector& v )
{
   return inv_trans*v;
}

   // coverts the point to object coordinates
Point Coordinates::ToObject( const Point& p )
{
   return inv_trans*p;
}
