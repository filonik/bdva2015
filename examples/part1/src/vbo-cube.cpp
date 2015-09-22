#include "vbo-cube.h"

VBOCube::VBOCube()
{
   m_fScaleX = m_fScaleY = m_fScaleZ = 1.0f;
   m_fTranslateX = m_fTranslateY = m_fTranslateZ = 0.0f;
   
   init();
}

VBOCube::VBOCube(float sx, float sy, float sz, float tx, float ty, float tz)
{
   m_fScaleX = sx;
   m_fScaleY = sy;
   m_fScaleZ = sz;
   m_fTranslateX = tx;
   m_fTranslateY = ty;
   m_fTranslateZ = tz;
   
   init();
}

void VBOCube::init()
{
   float side = 1.0f;
   float side2 = side / 2.0f;
   
   float v[24*3] =
   {
      // Front
      -side2, -side2, side2,
       side2, -side2, side2,
       side2,  side2, side2,
      -side2,  side2, side2,
      // Right
       side2, -side2, side2,
       side2, -side2, -side2,
       side2,  side2, -side2,
       side2,  side2, side2,
      // Back
      -side2, -side2, -side2,
      -side2,  side2, -side2,
       side2,  side2, -side2,
       side2, -side2, -side2,
      // Left
      -side2, -side2, side2,
      -side2,  side2, side2,
      -side2,  side2, -side2,
      -side2, -side2, -side2,
      // Bottom
      -side2, -side2, side2,
      -side2, -side2, -side2,
       side2, -side2, -side2,
       side2, -side2, side2,
      // Top
      -side2,  side2, side2,
       side2,  side2, side2,
       side2,  side2, -side2,
      -side2,  side2, -side2
   };
   
   float n[24*3] =
   {
      // Front
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      // Right
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      // Back
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      // Left
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      // Bottom
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      // Top
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f
   };
   
   float tex[24*2] =
   {
      // Front
      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      // Right
      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      // Back
      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      // Left
      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      // Bottom
      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      // Top
      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f
   };
   
   GLuint el[] =
   {
       0, 1, 2,  0, 2, 3,
       4, 5, 6,  4, 6, 7,
       8, 9,10,  8,10,11,
      12,13,14, 12,14,15,
      16,17,18, 16,18,19,
      20,21,22, 20,22,23
   };
   
   for (int i=0; i<24; i++)
   {
      v[i*3+0] *= m_fScaleX;
      v[i*3+1] *= m_fScaleY;
      v[i*3+2] *= m_fScaleZ;
      v[i*3+0] += m_fTranslateX;
      v[i*3+1] += m_fTranslateY;
      v[i*3+2] += m_fTranslateZ;
   }
   
   glGenVertexArrays( 1, &vaoHandle );
   glBindVertexArray(vaoHandle);
   
   unsigned int handle[4];
   glGenBuffers(4, handle);
   
   glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
   glBufferData(GL_ARRAY_BUFFER, 24*3*sizeof(float), v, GL_STATIC_DRAW);
   glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
   glEnableVertexAttribArray(0); // vertex position
   
   glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
   glBufferData(GL_ARRAY_BUFFER, 24*3*sizeof(float), n, GL_STATIC_DRAW);
   glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
   glEnableVertexAttribArray(1); // vertex normal
   
   glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
   glBufferData(GL_ARRAY_BUFFER, 24*2*sizeof(float), tex, GL_STATIC_DRAW);
   glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
   glEnableVertexAttribArray(2); // texture coords
   
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36*sizeof(GLuint), el, GL_STATIC_DRAW);
   
   glBindVertexArray(0);
}


void VBOCube::render()
{
   glBindVertexArray(vaoHandle);
   glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}

