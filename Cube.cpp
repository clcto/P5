#include "Cube.h"

#include <cmath>
#include <iostream>
#include <limits>

using std::cout;

RayHit* Cube::Intersects( const Ray& ray )
{
   Point start = - coord.ToObject( ray.Start() );
   Vector start_v = Vector( start );
   start_v[W] = 0;

   Vector dir  = coord.ToObject( ray.Direction() );
   double time_scale = 1/dir.Length();
   dir *= time_scale;

   Vector n, n_min;
   double t, t_min;

   t_min = numeric_limits<double>::max();

   bool hit = false;

      // z = 0 plane d = 0
   n.Set( 0, 0, -1 );
   if( n * -dir )
   {
      t = ( n * start_v + 0 )/( n * -dir );

      if( t > 0 && t < t_min )
      {
         hit = true;
         t_min = t;
         n_min = n;
      }
   }

      // z = 1 plane d = -1
   n.Set( 0, 0, 1 );
   if( n * -dir )
   {
      t = ( n * start_v - 1 )/(n * -dir );

      if( t > 0 && t < t_min )
      {
         hit = true;
         t_min = t;
         n_min = n;
      }
   }

      // y = 0 plane d = 0
   n.Set( 0, -1, 0 );
   if( n * -dir )
   {
      t = ( n * start_v + 0 )/(n * -dir );

      if( t > 0 && t < t_min )
      {
         hit = true;
         t_min = t;
         n_min = n;
      }
   }

      // y = 1 plane d = -1
   n.Set( 0, 1, 0 );
   if( n * -dir )
   {
      t = ( n * start_v - 1 )/(n * -dir );

      if( t > 0 && t < t_min )
      {
         hit = true;
         t_min = t;
         n_min = n;
      }
   }

      // x = 0 plane d = 0
   n.Set( -1, 0, 0 );
   if( n * -dir )
   {
      t = ( n * start_v + 0 )/(n * -dir );

      if( t > 0 && t < t_min )
      {
         hit = true;
         t_min = t;
         n_min = n;
      }
   }

      // x = 1 plane d = -1
   n.Set( 1, 0, 0 );
   if( n * -dir )
   {
      t = ( n * start_v - 1 )/(n * -dir );

      if( t > 0 && t < t_min )
      {
         hit = true;
         t_min = t;
         n_min = n;
      }
   }
   std::cout << "n_min: " << n_min << "\n";
   
   
   if( !hit )
      return NULL; 

      // closest plane is outside the bounds of the
      // cube. Doesn't intersect.
   if( n_min * -dir < 0 )
      return NULL; 


   n = coord.ToWorld( n_min );

   return new RayHit( ray, t * time_scale, n, this );
}
