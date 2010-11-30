#include "Coordinates.h"

/* Instance Variables -------
      Matrix trans, inv_trans;
*/

Coordinates()
{
   trans.Set(
      0, 0, 0, 0,
      0, 0, 0, 0,
      0, 0, 0, 0,
      0, 0, 0, 1 );

   inv_trans.Set(
      0, 0, 0, 0,
      0, 0, 0, 0,
      0, 0, 0, 0,
      0, 0, 0, 1 );
}

Coordinates( const Point& t, const Vector& s )
{
   trans.Set(
      s[X],    0,    0, t[X],
         0, s[Y],    0, t[Y],
         0,    0, s[Z], t[Z],
         0,    0,    0,    1 );

   inv_trans.Set(
      1/s[X],      0,      0, -t[X],
           0, 1/s[Y],      0, -t[Y],
           0,      0, 1/s[Z], -t[Z],
           0,      0,      0,     1 );
}

Vector ToWorld( const Vector& v )
{
   return trans*v;
}

Point  ToWorld( const Point& p )
{
   return trans*p;
}

Vector ToObject( const Vector& v )
{
   return inv_trans*v;
}

Point  ToObject( const Point& p )
{
   return inv_trans*p;
}
