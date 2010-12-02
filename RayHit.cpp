// --------------------------------------------------------
// RayHit
//    stores the data about a hit
//       where, what object, what time, what ray
//
// Carick Wienke
// --------------------------------------------------------

#include "RayHit.h"

   // create a RayHit:
   //    r: ray that hits object
   //    t: time of hit
   //    n: normal to the surface
   //    s: shape that is hit
RayHit::RayHit( const Ray& r, double t, 
                const Vector& n, Shape* s )
{
   time = t;
   ray = r;
   hit = ray.At( t );
   normal = n;
   normal.Normalize();
   shape = s;
}

   // return the time of hit
double RayHit::Time() const
{
   return time;
}

   // return normal to surface
const Vector& RayHit::Normal() const
{
   return normal;
}

   // return shape hit
Shape* RayHit::Face() const
{
   return shape;
}

   // return point of hit
const Point& RayHit::HitPoint() const
{
   return hit;
}

   // return input ray
const Ray& RayHit::InRay() const
{
   return ray;
}

   // compare if the two hit the same spot
   // within a margin of error
bool RayHit::operator==( const RayHit& other ) const
{
   return 
      shape == other.shape &&
      fabs( hit[X] - other.hit[X]) < err &&
      fabs( hit[Y] - other.hit[Y]) < err &&
      fabs( hit[Z] - other.hit[Z]) < err;
}
