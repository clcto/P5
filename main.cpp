#include "Shape.h"
#include "Sphere.h"
#include "Cube.h"
#include "Scene.h"
#include "RayHit.h"

#include <cstring>
#include <iostream>
#include <vector>
using std::vector;
using std::cout;

void draw()
{
   Scene::Instance()->Render();
}

void test()
{
   cout << "Format:\n[Start Point]\n[Direction Vector]\n"
        << "[Expected intersection]\n[Calculated]\n\n";
   cout << "Expected values = [999 999 999 1] are 'misses\n\n";

   cout << "Creating Cube at (1,1,1) to (2,2,2)\n\n";

   Cube c;
   c.Translate( 1, 1, 1 );
   
   vector<Point> starts;
   vector<Vector> directions;
   vector<Point> expect;

   starts.push_back( Point( 10, 1.5, 1.5 ) );
   directions.push_back( Vector( -1, 0, 0 ) );
   expect.push_back( Point( 2, 1.5, 1.5 ) );

   starts.push_back( Point( 3, 2.5, 2.5 ) );
   directions.push_back( Vector( -1, -1, -1 ) );
   expect.push_back( Point( 2, 1.5, 1.5 ) );

   starts.push_back( Point( 1.5, 10, 1.5 ) );
   directions.push_back( Vector( 0, -1, 0 ) );
   expect.push_back( Point( 1.5, 2, 1.5 ) );

   starts.push_back( Point( 2.5, 3, 2.5 ) );
   directions.push_back( Vector( -1, -1, -1 ) );
   expect.push_back( Point( 1.5, 2, 1.5 ) );

   starts.push_back( Point( 1.5, 1.3, 12 ) );
   directions.push_back( Vector( 0, 0, -1 ) );
   expect.push_back( Point( 1.5, 1.3, 2 ) );

   starts.push_back( Point( 2.5, 2.5, 3 ) );
   directions.push_back( Vector( -1, -1, -1 ) );
   expect.push_back( Point( 1.5, 1.5, 2 ) );

   starts.push_back( Point( 3, 2, 2 ) );
   directions.push_back( Vector( 1, 1, -1 ) );
   expect.push_back( Point( 999,999,999 ) );

   starts.push_back( Point( 2, 1.8, 2 ) );
   directions.push_back( Vector( -2, -1, -2 ) );
   expect.push_back( Point( 999, 999, 999 ) );

   for( uint i = 0; i < starts.size(); ++i )
   {
      cout << starts[i] << "\n" << directions[i] << "\n"
           << expect[i] << "\n";
      
      Ray r ( starts[i], directions[i] );
      RayHit *rh = c.Intersects( r );
      if( rh )
         cout << rh->HitPoint() << "\n\n";
      else
         cout << "NO HIT\n\n";
   }

   cout << "Creating sphere at 0,0,0 with radius 1\n";

   Sphere s;

   vector<Point> starts2;
   vector<Vector> directions2;
   vector<Point> expect2;

   starts2.push_back( Point( 10, 10, 10 ) );
   directions2.push_back( Vector( -1, -1, -1 ) );
   expect2.push_back( Point( .577, .577, .577 ) );

   starts2.push_back( Point( 10, 10, 0 ) );
   directions2.push_back( Vector( -1, -1, 0 ) );
   expect2.push_back( Point( .707, .707, 0 ) );

   starts2.push_back( Point( 2, 0, 0 ) );
   directions2.push_back( Vector( -1, 1, 0 ) );
   expect2.push_back( Point( 999, 999, 999 ) );

   for( uint i = 0; i < starts2.size(); ++i )
   {
      cout << starts2[i] << "\n" << directions2[i] << "\n"
           << expect2[i] << "\n";
      
      Ray r ( starts2[i], directions2[i] );
      RayHit *rh = s.Intersects( r );
      if( rh )
         cout << rh->HitPoint() << "\n\n";
      else
         cout << "NO HIT\n\n";
   }
}


int main( int argc, char** argv )
{
   if( argc > 1 && !strcmp( argv[1], "-test" ) )
   {
      test();
      return 0;
   }

   Scene::Instance()->Create();

   Scene::Instance()->Init( argc, argv );

   glutDisplayFunc( draw );

   glutMainLoop();
}
