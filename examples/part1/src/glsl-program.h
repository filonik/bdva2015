#ifndef __GLSL_PROGRAM_H__
#define __GLSL_PROGRAM_H__

#pragma warning( disable : 4290 )

#include <string>
#include <map>

#include <GL/glew.h>

#include <string>
#include <stdexcept>

#include <glm/glm.hpp>

/////////////////////////////////////////////////////////////////////////////

class GLSLProgramException : public std::runtime_error 
{
public:
   GLSLProgramException(const std::string & msg) :
      std::runtime_error(msg) {}
};

/////////////////////////////////////////////////////////////////////////////

class GLSLProgram
{
public:
   enum GLSLShaderType
   {
      VERTEX = GL_VERTEX_SHADER,
      FRAGMENT = GL_FRAGMENT_SHADER,
      GEOMETRY = GL_GEOMETRY_SHADER,
      TESS_CONTROL = GL_TESS_CONTROL_SHADER,
      TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
      COMPUTE = GL_COMPUTE_SHADER
   };
   
   GLSLProgram(); 
   
   void compileShader(
      const std::string &source,
      GLSLProgram::GLSLShaderType type)
      throw (GLSLProgramException);
   
   void compileShaderFromFile(
      const std::string &fileName,
      GLSLProgram::GLSLShaderType type)
      throw (GLSLProgramException);
   
   void link()
      throw (GLSLProgramException);
   
   void use();
   void unUse();
   
   void bindAttribLocation(GLuint location, const char *name);
   
   GLuint getUniformLocation(const char *name);
   
   void setUniform(const char *name, const glm::mat4 &m);
   void setUniform(const char *name, const glm::mat3 &m);
   void setUniform(const char *name, const glm::vec4 &v);
   void setUniform(const char *name, float x, float y, float z);
   void setUniform(const char *name, float f);
   
   GLuint getHandle();
   bool isLinked();
   bool isBound();

private:
   GLuint m_uiHandle;
   bool m_bLinked;
   bool m_bBound;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __GLSL_PROGRAM_H__
