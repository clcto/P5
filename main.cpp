#include "Shape.h"
#include "Sphere.h"
#include "Cube.h"
#include "Scene.h"
#include "RayHit.h"

#include <iostream>


void draw()
{
   Scene::Instance()->Render();
}

int main( int argc, char** argv )
{

   Scene::Instance()->Create();

   Scene::Instance()->Init( argc, argv );

   //Ray r = Ray( Point( 10, .5, .5 ), Vector( -1, 0, 0 ) );
   //RayHit* rh = c1.Intersects( r );

   glutDisplayFunc( draw );

   glutMainLoop();
}
