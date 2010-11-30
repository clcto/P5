#ifndef SPHERE_H_
#define SPHERE_H_

#include "Shape.h"

class Sphere : public Shape
{
   public:
      Sphere();
      ~Sphere();

      virtual void Intersects( const Ray& );

   private:
      Point center;

};

#endif
