#include "RayHit.h"

RayHit::RayHit( double t,  const Vector& n )
{
   time = t;
   normal = n;
   normal.Normalize();
}

double RayHit::Time() const
{
   return time;
}

const Vector& RayHit::Normal() const
{
   return normal;
}
