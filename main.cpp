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


   Sphere s1, s2;
   s1.Translate( Point( 3, 0, 0) );
   s1.Scale( 2, 2, 2 );
   s1.SetMaterial( Material::SHINY_RED );

   s2.Translate( Point( 2, -2, 2 ) );
   s2.Scale( 1, 1, 1 );
   s2.SetMaterial( Material::SHINY_BLUE );

   Cube c1;
   c1.SetMaterial( Material::SHINY_GREEN );
   c1.Translate( Point( -2, 1, 1 ) );
   c1.Scale( 1, 2, 1 );


   Scene::Instance()->AddShape( &s1 );
   Scene::Instance()->AddShape( &s2 );
   Scene::Instance()->AddShape( &c1 );

   Scene::Instance()->Init( argc, argv );

   //Ray r = Ray( Point( 10, .5, .5 ), Vector( -1, 0, 0 ) );
   //RayHit* rh = c1.Intersects( r );

   glutDisplayFunc( draw );

   glutMainLoop();
}
