// --------------------------------------------------------
// Cube
//    a shape that represents a cube (or rectangular prism)
//
// Carick Wienke
// --------------------------------------------------------

#include "Cube.h"

#include <cmath>
#include <iostream>
#include <limits>

using std::cout;

   // where does the ray hit the cube
RayHit* Cube::Intersects( const Ray& ray )
{
   Point start = coord.ToObject( ray.Start() );
   Vector start_v = Vector( start );
   start_v[W] = 0;

   Vector dir  = coord.ToObject( ray.Direction() );
   double time_scale = 1/dir.Length();
   dir *= time_scale;

   Ray tRay = Ray( start, dir );

   Vector n, n_min;
   double t, t_min;

   t_min = numeric_limits<double>::max();

   bool hit = false;

   for( int i = 0; i < 3; ++i )
   {
      n.Set( 0, 0, 0 );
      n[i] = -1;
      if( dir[i] > 0)
      {
         t = -start[i]/dir[i];

         if( t > 0 && t < t_min )
         {
            Point p = tRay.At( t );
            if( -0.005 <= p[X] && p[X] <= 1.005 &&
                -0.005 <= p[Y] && p[Y] <= 1.005 &&
                -0.005 <= p[Z] && p[Z] <= 1.005 )
            {
               hit = true;
               t_min = t;
               n_min = n;
            }
         }
      }

      n[i] = 1;
      if( -dir[i] > 0 )
      {
         t = (1-start[i])/dir[i];

         if( t > 0 && t < t_min )
         {
            Point p = tRay.At( t );

            if( -0.005 <= p[X] && p[X] <= 1.005 &&
                -0.005 <= p[Y] && p[Y] <= 1.005 &&
                -0.005 <= p[Z] && p[Z] <= 1.005 )
            {
               hit = true;
               t_min = t;
               n_min = n;
            }
         }
      }
   }

   
   if( !hit )
      return NULL; 

      // closest plane is outside the bounds of the
      // cube. Doesn't intersect.
   if( n_min * -dir < 0 )
      return NULL; 


   n = coord.ToWorld( n_min );

   return new RayHit( ray, t_min * time_scale, n, this );
}
