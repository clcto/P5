#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <string>

#include "Shape.h"
#include "RayHit.h"

using std::vector;
using std::string;

class Scene
{
   public:
      static Scene* Instance();
      void AddShape( Shape* );
      RayHit* findClosest( const Ray& );

      ~Scene();

   private:
      Scene();

         // holds the shapes on the screen
      vector<Shape*> shapes;

      static Scene* instance;
};

#endif // SCENE_H_
