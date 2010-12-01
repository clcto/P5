#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

#include "Scene.h"
#include "Sphere.h"

Scene* Scene::instance = NULL;

   // -----------------------------------------------------
   // singleton pattern to get the sole scene
Scene* Scene::Instance()
{
   if( !instance )
      instance = new Scene();
   return instance;
}

   // -----------------------------------------------------
   //  Constructor
Scene::Scene() 
{
   eye_x = -20;
   eye_y = 40;
   eye_z = 30;

   ambient.red = 0.4;
   ambient.blue = 0.4;
   ambient.green = 0.4;

   light.position[0] = 0;
   light.position[1] = 30;
   light.position[2] = 30;

   light.ambient.red = .1;
   light.ambient.blue = .1;
   light.ambient.green = .1;

   light.diffuse.red = 1;
   light.diffuse.blue = 1;
   light.diffuse.green = 1;

   light.specular.red = 0.8;
   light.specular.blue = 0.8;
   light.specular.green = 0.8;
}

Scene::~Scene()
{
   while( !shapes.empty() )
   {
      delete shapes.back();
      shapes.pop_back();
   }
}

RayHit* Scene::FindClosest( const Ray& r )
{
   RayHit *closest = NULL;
   
   std::vector<Shape*>::iterator it;

   for( it = shapes.begin(); it < shapes.end(); ++it )
   {
      RayHit* hit = (*it)->Intersects( r );
      if( closest && hit && hit->Time() < closest->Time() )
         closest = hit;
      else if( hit && !closest )
         closest = hit;
   }

   return closest;
}

   // -----------------------------------------------------
   // adds a shape to the scene
void Scene::AddShape( Shape* newShape )
{
   shapes.push_back( newShape );
}

void Scene::Render()
{
   GLint viewport[4];
   glGetIntegerv( GL_VIEWPORT, viewport );

   GLdouble projection[16];
   glGetDoublev( GL_PROJECTION_MATRIX, projection );

   GLdouble modelview[16];
   glGetDoublev( GL_MODELVIEW_MATRIX, modelview );

   float pixels[WIN_HEIGHT][WIN_WIDTH][3];

   for( int x = 0; x < WIN_WIDTH; ++x )
   {
      for( int y = 0; y < WIN_HEIGHT; ++y )
      {
         GLdouble vpX = x;
         GLdouble vpY = y;
         GLdouble vpZ = 0.0;

         GLdouble worldX, worldY, worldZ;

         gluUnProject( vpX, vpY, vpZ, modelview,
            projection, viewport, &worldX, &worldY,
            &worldZ );

         Point s  = Point( worldX, worldY, worldZ );
         Vector d = Vector( worldX - eye_x,
                            worldY - eye_y, 
                            worldZ - eye_z ); 

         Ray r = Ray( s, d );

         RayHit* rh = Scene::Instance()->FindClosest( r );

         Color c = Shade( rh, MAX_DEPTH );
         pixels[y][x][0] = c.red;
         pixels[y][x][1] = c.green;
         pixels[y][x][2] = c.blue;
#if 0
         pixels[y][x][0] = 1;
         pixels[y][x][1] = 1;
         pixels[y][x][2] = 1;
#endif
         
      }
   }
   
   glDrawPixels( WIN_WIDTH, WIN_HEIGHT, 
                 GL_RGB, GL_FLOAT, pixels );

   glutSwapBuffers();
}

void Scene::Init( int argc, char** argv )
{
   glutInit( &argc, argv );
   glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
   glutInitWindowSize( WIN_WIDTH, WIN_HEIGHT );
   glutCreateWindow( "Ray Tracing - c.wienke" );

   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluPerspective( 10, (double)WIN_WIDTH/WIN_HEIGHT, 
                   5, 100 );

   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   gluLookAt( eye_x, eye_y, eye_z, 0, 0,  0, 0, 0, 1 );

} 

Color Scene::Shade( RayHit* rh, int depth )
{
   if( rh )
   {
      Color color = {0, 0, 0};

      Color ka = rh->Face()->GetMaterial().ka();

      color.red += ka.red * ambient.red;
      color.blue += ka.blue * ambient.blue;
      color.green += ka.green * ambient.green;

      Color specRefl = SpecularReflection( *rh, depth );
      Color ks = rh->Face()->GetMaterial().ks();
      color.red += ks.red * specRefl.red;
      color.blue += ks.blue * specRefl.blue;
      color.green += ks.green * specRefl.green;

      Color direct = Direct( *rh );
      color.red += direct.red;
      color.blue += direct.blue;
      color.green += direct.green;

      return color;
   }
   else
   {
      Color color = { 1, 1, 1 };
      return color;
   }
}

Color Scene::Direct( RayHit rh )
{
   Point p = Point( light.position[0],
                    light.position[1],
                    light.position[2] );

   Vector v = Vector( rh.HitPoint() - p );
   v[W] = 0;
   Ray r = Ray( p, v );

   RayHit* lightHit = FindClosest( r );

   Color direct = {0,0,0};

   if( lightHit && *lightHit == rh )
   {
      Color kd = rh.Face()->GetMaterial().kd();
      
      direct.red = kd.red * light.diffuse.red *
                   -r.Direction() * rh.Normal();
      direct.blue = kd.blue * light.diffuse.blue *
                   -r.Direction() * rh.Normal();
      direct.green = kd.green * light.diffuse.green *
                   -r.Direction() * rh.Normal();

      Color ks = rh.Face()->GetMaterial().ks();
      float exp = rh.Face()->GetMaterial().exp();

      Vector refl = r.Direction() - 2 *
                    ( rh.Normal()*r.Direction() ) *
                    rh.Normal();
                 
      direct.red += ks.red * light.specular.red *
          pow( refl * rh.InRay().Direction(), exp );
      direct.blue += ks.blue * light.specular.blue *
          pow( refl * rh.InRay().Direction(), exp );
      direct.green += ks.green * light.specular.green *
          pow( refl * rh.InRay().Direction(), exp );
      
   }
   return direct;
}

Color Scene::SpecularReflection( RayHit rh, int depth )
{
   if( depth > 0 )
   {
      Point reflStart = rh.HitPoint();
      Vector reflDir = 
         rh.InRay().Direction() - 2 *
         (rh.InRay().Direction() * rh.Normal()) *
         rh.Normal();

      Ray tempRay = Ray( reflStart, reflDir );
      
         // move start off of object
      Ray refl = Ray( tempRay.At( 0.05 ), reflDir );

      RayHit* reflHit = FindClosest( refl );
      if( reflHit )
         return Shade( reflHit, depth - 1 );
   }

   Color c = {0,0,0};
   return c;

}
