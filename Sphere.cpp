#include "Sphere.h"
#include <cmath>
#include <iostream>

using std::cout;

Sphere::Sphere()
{
}

Sphere::~Sphere()
{

}

void Sphere::Intersects( const Ray& ray )
{
   Point start = -ray.Start();
   Vector dir   = ray.Direction();

      // ( C - R_o ) dot ( C - R_o ) - r^2
      // r = 1, so r^2 = 1
   double c = start[X] * start[X] +
              start[Y] * start[Y] +
              start[Z] * start[Z] - 1; 
   
   double t_c = start[X] * dir[X] +
                start[Y] * dir[Y] +
                start[Z] * dir[Z];

      // check if outside and pointing away
   cout << "c = " << c << " t_c = " << t_c << "\n";

   if( c > 0 && t_c < 0 )
   {
      return;
   }

   double discrim = t_c * t_c - c;

      // no intersection
   cout << "disc = " << discrim << "\n";

   if( discrim < 0 )
   {
      cout << "disc = " << discrim << "\n";
      return;
   }
   
   double h = sqrt( discrim );

   double t = 0;

      // if outside
   if( c > 0 )
      t = t_c - h;
      
      // if inside
   else
      t = t_c + h;

   Point p = ray.At( t );
   

   cout << "time = " << t << "\n" << p << "\n";;
}
