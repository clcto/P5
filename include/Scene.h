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
      void AddShape( Shape* );
      RayHit* FindClosest( const Ray& );
      void Render();
      void Init( int, char** );
      void Create();

      Color Shade( RayHit*, int );
      Color Direct( RayHit );
      Color SpecularReflection( RayHit, int );

      ~Scene();

   private:
      Scene();

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
