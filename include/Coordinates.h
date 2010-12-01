#ifndef COORDINATES_H_
#define COORDINATES_H_

#include "Vector.h"
#include "Point.h"
#include "Matrix.h"

class Coordinates
{
   public:
      Coordinates();
      Coordinates( const Point&, const Vector& );

      Vector ToWorld( const Vector& );
      Point  ToWorld( const Point& );

      Vector ToObject( const Vector& );
      Point  ToObject( const Point& );

   private:
      
      Matrix trans, inv_trans;

};

#endif
