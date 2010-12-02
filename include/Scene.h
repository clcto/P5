// --------------------------------------------------------
// Scene
//    holds the information about the scene.
//
//    what shapes are in the scene, what light
//    is there, and allows to "ray trace" the scene
//
// Carick Wienke
// --------------------------------------------------------

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <string>

#include "Shape.h"
#include "RayHit.h"
#include "Light.h"

using std::vector;
using std::string;

class Scene
{
   public:
      static Scene* Instance();

         // add a shape the scene to be drawn
      void AddShape( Shape* );

         // find the closest hit for the ray passed
      RayHit* FindClosest( const Ray& );

         // perform the ray tracing
      void Render();

         // init the GLUT Widnow
      void Init( int, char** );

         // create a default scene
      void Create();

      ~Scene();

   private:
      Scene();

         // gets the color at the point the ray hit
      Color Shade( RayHit*, int = MAX_DEPTH );

         // gets the color based on direct light
      Color Direct( RayHit );

         // gets the color based on the reflection
      Color SpecularReflection( RayHit, int );

         // holds the shapes on the screen
      vector<Shape*> shapes;
      
      float eye_x, eye_y, eye_z;

      Color ambient;
      Light light;

      static Scene* instance;
      static const int WIN_WIDTH = 640,
                       WIN_HEIGHT = 480;
      static const int MAX_DEPTH = 5;
};

#endif // SCENE_H_
