#ifndef __SCENE_3DS__
#define __SCENE_3DS__

#include "scene.h"

class Scene3DS : public Scene
{
public:
   void load3ds(const std::string& filename);

private:
   void readMeshChunk();
   void readObjectChunk();
   void readTrimeshChunk(Object* object);
   void readCameraChunk(void);
   void readMaterialChunk(void);
   std::string readTextureChunk(void);
   
   short fileGetWord();
   int fileGetInt();
   unsigned char fileGetUChar();
   float fileGetFloat(void);
   std::string fileGetName(void);
   std::string fileGetObjectName();
   
};

#endif // __SCENE_3DS__