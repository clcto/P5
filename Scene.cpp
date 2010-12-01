#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

#include "Scene.h"
#include "Sphere.h"
#include "Cube.h"

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
   eye_x = 20;
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

void Scene::Create()
{
   Sphere* center = new Sphere();
   center->Scale( 2, 2, 2 );
   center->SetMaterial( Material::SHINY_RED );
   AddShape( center );

   Sphere* sph_pos_x = new Sphere();
   sph_pos_x->Translate( 3.2, 0, -.4 );
   sph_pos_x->SetMaterial( Material::SHINY_BLUE );
   AddShape( sph_pos_x );

   Sphere* sph_pos_y = new Sphere();
   sph_pos_y->Translate( 0, 3, -.5 );
   sph_pos_y->Scale( .75, .75, .75 );
   sph_pos_y->SetMaterial( Material::SHINY_GREEN );
   AddShape( sph_pos_y );

   Cube* bottom = new Cube();
   bottom->Translate( -4, -4, -4 );
   bottom->Scale( 8, 8, .5 );
   bottom->SetMaterial( Material::PIANO_BLACK );
   AddShape( bottom );

   Cube* back_left = new Cube();
   back_left->Translate( -4, -4, -4 );
   back_left->Scale(8, -0.5, 8 );
   back_left->SetMaterial( Material::SHINY_GREEN );
   AddShape( back_left );

   Cube* back_right = new Cube();
   back_right->Translate( -4.48, -4, -4 );
   back_right->Scale( .5, 8, 8 );
   back_right->SetMaterial( Material::SHINY_BLUE );
   AddShape( back_right );
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
      if( !direct.red && !direct.blue && !direct.green )
      {
         color.red *= 0.6;
         color.blue *= 0.6;
         color.green *= 0.6;
      }
      else
      {
         color.red += direct.red;
         color.blue += direct.blue;
         color.green += direct.green;
      }

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
      Ray refl = Ray( tempRay.At( 0.1 ), reflDir );

      RayHit* reflHit = FindClosest( refl );
      if( reflHit )
         return Shade( reflHit, depth - 1 );
   }

   Color c = {0,0,0};
   return c;

}
