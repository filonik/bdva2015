#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

/////////////////////////////////////////////////////////////////////////////

class Object
{
public:
   Object();
   ~Object();
   
   std::string getName();
   
   void addVertex(glm::vec3 vertex);
   void addFace(glm::uvec3 face);
   
   void init();
   void render();
   
   GLuint getNumberOfVertices();
   GLuint getNumberOfFaces();
   
private:
   std::string m_sName;
   
   void calculateNormals();
   
   std::vector<glm::vec3> m_akVertices;
   std::vector<glm::vec3> m_akNormals;
   std::vector<glm::uvec3> m_akFaces;
   
   GLuint m_uiVAOHandle;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __OBJECT_H__
