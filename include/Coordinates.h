#ifndef COORDINATES_H_
#define COORDINATES_H_

#include "Vector.h"
#include "Point.h"
#include "Matrix.h"

class Coordinates
{
   public:
      Coordinates();

      Vector ToWorld( const Vector& );
      Point  ToWorld( const Point& );

      Vector ToObject( const Vector& );
      Point  ToObject( const Point& );

      void Scale( double, double, double );
      void Translate( const Point& );

   private:
      
      Matrix trans, inv_trans;

};

#endif
