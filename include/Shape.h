#ifndef SHAPE_H_
#define SHAPE_H_

#include <GL/glut.h>
#include <cmath>

#include "Coordinates.h"
#include "Point.h"
#include "Matrix.h"
#include "Material.h"
#include "Ray.h"
#include "RayHit.h"

class RayHit;

class Shape
{

   public: //------------------------------------------

         // SetTransformation
      void Translate( const Point& p );
      void Translate( float, float, float ); 
      void Scale( float, float, float ); 

         // change how the shape reacts to light
      void SetMaterial( const Material& m );

      Material GetMaterial() const;

      virtual RayHit* Intersects( const Ray& ) = 0;

   protected: // --------------------------------------

      Coordinates coord;

      Material material;
};

#endif /*SHAPE_H_*/
