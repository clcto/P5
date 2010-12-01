#ifndef RAYHIT_H_
#define RAYHIT_H_

#include "Vector.h"

class RayHit
{
   public:
      RayHit( double, const Vector& );

      double Time() const;
      const Vector& Normal() const;

   protected:

      double time;
      Vector normal;

};
#endif
