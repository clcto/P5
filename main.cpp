#include "Shape.h"
#include <iostream>

int main( void )
{
   Matrix m, a;
   m.Set( 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4 );
   a = m;

   std::cout << a*m;
}
