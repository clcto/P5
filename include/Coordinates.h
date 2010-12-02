// --------------------------------------------------------
// Coordinates
//    class that represents a coordinate system
//    (for an object). It allows for transforming
//    between the world and object coordinates
//
// Carick Wienke
// --------------------------------------------------------

#ifndef COORDINATES_H_
#define COORDINATES_H_

#include "Vector.h"
#include "Point.h"
#include "Matrix.h"

class Coordinates
{
   public:
      Coordinates();

         // convert to world coordinates
      Vector ToWorld( const Vector& );
      Point  ToWorld( const Point& );

         // convert to object coordinates
      Vector ToObject( const Vector& );
      Point  ToObject( const Point& );

         // change the coordinate system
      void Scale( double, double, double );
      void Translate( const Point& );

   private:
         // matrix to transform to and from
         // world coordinates
      Matrix trans, inv_trans;
};

#endif
