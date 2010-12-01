#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <sstream>

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
}

Scene::~Scene()
{
   while( !shapes.empty() )
   {
      delete shapes.back();
      shapes.pop_back();
   }
}

RayHit* Scene::findClosest( const Ray& r )
{
   RayHit *closest = NULL;
   
   std::vector<Shape*>::iterator it;

   for( it = shapes.begin(); it < shapes.end(); ++it )
   {
      RayHit* hit = (*it)->Intersects( r );
      if( closest && hit && hit->Time() > closest->Time() )
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
