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

Coordinates::Coordinates( const Point& t, const Vector& s )
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

void Coordinates::SetTranslation( const Point& p )
{
   trans = trans * Matrix( 1, 0, 0, p[X],
                           0, 1, 0, p[Y],
                           0, 0, 1, p[Z],
                           0, 0, 0, 1 );
   /*
   trans[0][3] = p[X];
   trans[1][3] = p[Y];
   trans[2][3] = p[Z];
   */
   inv_trans = Matrix( 1, 0, 0, -p[X],
                       0, 1, 0, -p[Y],
                       0, 0, 1, -p[Z],
                       0, 0, 0, 1 )    * inv_trans;
   /*
   inv_trans[0][3] = -p[X];
   inv_trans[1][3] = -p[Y];
   inv_trans[2][3] = -p[Z];
   */
}

void Coordinates::SetScale( double x, double y, double z )
{
   trans = trans * Matrix( x, 0, 0, 0,
                           0, y, 0, 0,
                           0, 0, z, 0,
                           0, 0, 0, 1 );
   cout << trans << '\n';
   /*
   trans[0][0] = x;
   trans[1][1] = y;
   trans[2][2] = z;
   */

   inv_trans = Matrix( 1/x, 0, 0, 0,
                       0, 1/y, 0, 0,
                       0, 0, 1/z, 0,
                       0, 0, 0, 1 )  * inv_trans;

   /*
   inv_trans[0][0] = 1/x;
   inv_trans[1][1] = 1/y;
   inv_trans[2][2] = 1/z;
   */
}
