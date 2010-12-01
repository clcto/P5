#include "Sphere.h"

#include <cmath>
#include <iostream>

using std::cout;

RayHit* Sphere::Intersects( const Ray& ray )
{
   Point start = - coord.ToObject( ray.Start() );
   cout << "ws: " << -ray.Start() << "\n";
   cout << "os: " << start << "\n";

   Vector dir  = coord.ToObject( ray.Direction() );
   double time_scale = 1/dir.Length();
   dir *= time_scale;
   cout << "wd: " << ray.Direction() << "\n";
   cout << "od: " << dir << "\n";



      // ( C - R_o ) dot ( C - R_o ) - r^2
      // r = 1, so r^2 = 1
   double c = start[X] * start[X] +
              start[Y] * start[Y] +
              start[Z] * start[Z] - 1; 
   
   double t_c = start[X] * dir[X] +
                start[Y] * dir[Y] +
                start[Z] * dir[Z];

      // check if outside and pointing away

   if( c > 0 && t_c < 0 )
   {
      return NULL;
   }

   double discrim = t_c * t_c - c;

      // no intersection

   if( discrim < 0 )
   {
      return NULL;
   }
   
   double h = sqrt( discrim );

   double t = 0;

      // if outside
   if( c > 0 )
      t = t_c - h;
      
      // if inside
   else
      t = t_c + h;

   Vector n = Vector( -start[X] + t*dir[X],
                      -start[Y] + t*dir[Y],
                      -start[Z] + t*dir[Z] );

   n = coord.ToWorld( n );

   return new RayHit( t * time_scale, n );
}
