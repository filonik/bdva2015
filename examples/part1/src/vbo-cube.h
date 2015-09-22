#ifndef __VBO_CUBE_H__
#define __VBO_CUBE_H__

#include <GL/glew.h>

class VBOCube
{
private:
   GLuint vaoHandle;
   float m_fScaleX, m_fScaleY, m_fScaleZ;
   float m_fTranslateX, m_fTranslateY, m_fTranslateZ;
   
   void init();
   
public:
   VBOCube();
   VBOCube(float sx, float sy, float sz, float tx, float ty, float tz);
   
   void render();
};

#endif // __VBO_CUBE_H__