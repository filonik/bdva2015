#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>

#include "object.h"

/////////////////////////////////////////////////////////////////////////////

class Scene
{
public:
	Scene();
   ~Scene();
   
   void addObject(Object *object);
   
   void render();
   
private:
   std::vector<Object*> m_akObjects;
   
   
   // objects
   // cameras
   // lights
   // materials
   //
   // std::vector<KDObject> objects;
	// std::vector<KDCamera> cameras;
	// std::vector<KDLight> ligths;
	// std::vector<KDMaterial3DS> materials;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __SCENE_H__