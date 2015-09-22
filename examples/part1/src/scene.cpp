#include "scene.h"

#include <iostream>
#include <vector>

Scene::Scene()
{
   m_akObjects.clear();

   std::cout << "#constructor scene#\n";
   
}


Scene::~Scene()
{
   std::cout << "#detructor scene#\n";
   
   for (std::vector<Object*>::iterator iter = m_akObjects.begin(); iter != m_akObjects.end(); iter++)
   {
      delete *iter;
   }
}


void Scene::addObject(Object *object)
{
   m_akObjects.push_back(object);
}

void Scene::render()
{
   for (std::vector<Object*>::iterator iter = m_akObjects.begin(); iter != m_akObjects.end(); iter++)
   {
      Object *object = *iter;
      object->render();
      //std::cout << "*v" << object->getNumberOfVertices() << "-f" << object->getNumberOfFaces();
      break;
   }
   //std::cout << "\n";
}

