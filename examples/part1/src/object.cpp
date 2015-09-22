#include "object.h"

#include <iostream>

Object::Object()
{
   m_akVertices.clear();
   m_akFaces.clear();
   m_akNormals.clear();
   
   std::cout << "#object constructor#\n";
}

Object::~Object()
{
   std::cout << "#object destructor#vortices#" << m_akVertices.size() << "#faces#" << m_akFaces.size() << "#\n";
   
   m_akVertices.clear();
   m_akFaces.clear();
   m_akNormals.clear();
}

std::string Object::getName()
{
   return m_sName;
}

void Object::addVertex(glm::vec3 vertex)
{
   m_akVertices.push_back(vertex);
}

void Object::addFace(glm::uvec3 face)
{
   m_akFaces.push_back(face);
}

void Object::init()
{
   calculateNormals();
   
   glGenVertexArrays(1, &m_uiVAOHandle);
   glBindVertexArray(m_uiVAOHandle);
   
   unsigned int handle[3];
   glGenBuffers(3, handle);

   glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
   glBufferData(GL_ARRAY_BUFFER, m_akVertices.size()*3*sizeof(float), m_akVertices.data(), GL_STATIC_DRAW);
   glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL+(0)));
   glEnableVertexAttribArray(0); // vertex position
   
   glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
   glBufferData(GL_ARRAY_BUFFER, m_akNormals.size()*3*sizeof(float), m_akNormals.data(), GL_STATIC_DRAW);
   glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL+(0)));
   glEnableVertexAttribArray(1); // vertex normal
   
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[2]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_akFaces.size()*3*sizeof(GLuint), m_akFaces.data(), GL_STATIC_DRAW);
   
   glBindVertexArray(0);
}

void Object::render()
{
   glBindVertexArray(m_uiVAOHandle);
   glDrawElements(GL_TRIANGLES, (unsigned int)m_akFaces.size()*3, GL_UNSIGNED_INT, ((GLubyte *)NULL+(0)));
}

GLuint Object::getNumberOfVertices()
{
   return (GLuint)m_akVertices.size();
}

GLuint Object::getNumberOfFaces()
{
   return (GLuint)m_akFaces.size();
}

void Object::calculateNormals()
{
   m_akNormals.resize(m_akVertices.size());
   for (size_t j=0; j<m_akFaces.size(); j++) m_akNormals[0]=glm::vec3(0, 0, 0);
   
   for (size_t i=0; i<m_akFaces.size(); i++)
   {
      glm::uvec3 f = m_akFaces[i];
      glm::vec3 v0 = m_akVertices[f.x];
      glm::vec3 v1 = m_akVertices[f.y];
      glm::vec3 v2 = m_akVertices[f.z];
      glm::vec3 e1 = v1-v0;
      glm::vec3 e2 = v2-v0;
      glm::vec3 N = glm::cross(e1, e2);
      m_akNormals[f.x] += N;
      m_akNormals[f.y] += N;
      m_akNormals[f.z] += N;
   }
   
   for (size_t i=0; i<m_akNormals.size(); i++)
   {
      m_akNormals[i] = glm::normalize(m_akNormals[i]);
   }
}




