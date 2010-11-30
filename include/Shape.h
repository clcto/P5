#ifndef SHAPE_H_
#define SHAPE_H_

#include <GL/glut.h>
#include <cmath>

#include "Point.h"
#include "Matrix.h"
#include "Material.h"
#include "Ray.h"

class Shape
{

   public: //------------------------------------------

      Shape();

      virtual ~Shape();
      
         // SetTransformation
      void SetTranslation( const Point& p );
      void SetScale( float, float, float ); 

         // change how the shape reacts to light
      void SetMaterial( const Material& m );

      virtual void Intersects( const Ray& ) = 0;

   protected: // --------------------------------------

         // transformation matrices
      Matrix location;
      Matrix scale;

         // inverse transformation matrices
      Matrix location_inv;
      Matrix scale_inv;

      Material material;
};

#endif /*SHAPE_H_*/
