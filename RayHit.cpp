#include "RayHit.h"

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

double RayHit::Time() const
{
   return time;
}

const Vector& RayHit::Normal() const
{
   return normal;
}

Shape* RayHit::Face() const
{
   return shape;
}

const Point& RayHit::HitPoint() const
{
   return hit;
}

const Ray& RayHit::InRay() const
{
   return ray;
}

bool RayHit::operator==( const RayHit& other ) const
{
   return 
      shape == other.shape &&
      fabs( hit[X] - other.hit[X]) < err &&
      fabs( hit[Y] - other.hit[Y]) < err &&
      fabs( hit[Z] - other.hit[Z]) < err;
}
