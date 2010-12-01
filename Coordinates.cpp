#include "Coordinates.h"

/* Instance Variables -------
      Matrix trans, inv_trans;
*/

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

Vector Coordinates::ToWorld( const Vector& v )
{
   return trans*v;
}

Point Coordinates::ToWorld( const Point& p )
{
   return trans*p;
}

Vector Coordinates::ToObject( const Vector& v )
{
   return inv_trans*v;
}

Point Coordinates::ToObject( const Point& p )
{
   return inv_trans*p;
}
