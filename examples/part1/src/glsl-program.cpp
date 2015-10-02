#include "glsl-program.h"

#include <fstream>
using std::ifstream;
#include <sstream>
#include <iostream>

namespace detail {
inline GLSLProgram::GLSLShaderType getTypeFromPath(const std::string& path)
{
	static std::map<std::string, GLSLProgram::GLSLShaderType> extensionToType = {
		{ ".cs", GLSLProgram::COMPUTE }, { ".comp", GLSLProgram::COMPUTE },
		{ ".vs", GLSLProgram::VERTEX }, { ".vert", GLSLProgram::VERTEX },
		{ ".tcs", GLSLProgram::TESS_CONTROL }, { ".tesc", GLSLProgram::TESS_CONTROL },
		{ ".tes", GLSLProgram::TESS_EVALUATION }, { ".tese", GLSLProgram::TESS_EVALUATION },
		{ ".gs", GLSLProgram::GEOMETRY }, { ".geom", GLSLProgram::GEOMETRY },
		{ ".fs", GLSLProgram::FRAGMENT }, { ".frag", GLSLProgram::FRAGMENT },
	};
	auto index = path.find_last_of(".");
	auto extension = path.substr(index, path.length() - index);
	return extensionToType[extension];
}
}

GLSLProgram::GLSLProgram() :
   m_uiHandle(0),
   m_bLinked(false),
   m_bBound(false)
{
}


GLuint GLSLProgram::getHandle()
{
   return m_uiHandle;
}


void GLSLProgram::use()
{
   if (m_uiHandle == 0 || (!m_bLinked))
      throw GLSLProgramException("shader has not been linked yet");
   glUseProgram(m_uiHandle);
   m_bBound = true;
}


void GLSLProgram::unUse()
{
   if (m_bBound == true)
   {
      glUseProgram(0);
      m_bBound = false;
   }
}


bool GLSLProgram::isLinked()
{
   return m_bLinked;
}


bool GLSLProgram::isBound()
{
   return m_bBound;
}


void GLSLProgram::compileShader(const std::string &source, GLSLProgram::GLSLShaderType type)
{
   if (m_uiHandle == 0)
   {
      m_uiHandle = glCreateProgram();
      if (m_uiHandle == 0)
      {
         throw GLSLProgramException("unable to create shader program");
      }
   }
   
   GLuint shaderHandle = glCreateShader(type);
   
   const char *c_code = source.c_str();
   glShaderSource(shaderHandle, 1, &c_code, NULL);
   
   glCompileShader(shaderHandle);
  
   //
   // check for errors here
   //
   
   // if all OK
   
   // glAttachShader(m_uiHandle, shaderHandle);
   int result;
   glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &result);

   if (result == GL_FALSE)
   {
      int length, slen;
      glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &length);
   
      GLchar* compiler_log = new GLchar[length];
      glGetShaderInfoLog(shaderHandle, length, &slen, compiler_log);
      std::cout << "compiler_log:\n" << compiler_log << std::endl;
      delete[] compiler_log;
      
      //
      // add error handling
      //
      //
      //
   }
   else
   {
      glAttachShader(m_uiHandle, shaderHandle);
   }
}


void GLSLProgram::compileShaderFromFile(const std::string &fileName, GLSLProgram::GLSLShaderType type)
{
   ifstream inFile(fileName, std::ios::in);
   if (!inFile)
   {
      std::string message = std::string("Unable to open: ") + fileName;
      throw GLSLProgramException(message);
   }
   
   std::stringstream code;
   code << inFile.rdbuf();
   inFile.close();
   
   compileShader(code.str(), type);
}

void GLSLProgram::compileShaderFromPath(const std::string& path, const std::vector<std::string>& arguments)
{
	auto type = detail::getTypeFromPath(path);

	std::string out, err;
	std::tie(out, err) = mcpp::process(path, arguments);

	//std::cout << out << std::endl;
	//std::cout << err << std::endl;

	compileShader(out, type);
}


void GLSLProgram::link()
{
   if (m_bLinked) return;
   
   if (m_uiHandle == 0)
      throw GLSLProgramException("program has not been compiled");
   
   glLinkProgram(m_uiHandle);
   
   //
   // check for errors here
   //
   
   // if all OK
   // clear uniforms
   
   m_bLinked = true;
}


void GLSLProgram::bindAttribLocation(GLuint location, const char *name)
{
   glBindAttribLocation(m_uiHandle, location, name);
}

GLuint GLSLProgram::getUniformLocation(const char *name)
{
   return glGetUniformLocation(m_uiHandle, name);
}

void GLSLProgram::setUniform(const char *name, const glm::mat4 &m)
{
   GLint location = getUniformLocation(name);
   glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
}

void GLSLProgram::setUniform(const char *name, const glm::mat3 &m)
{
   GLint location = getUniformLocation(name);
   glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]);
}

void GLSLProgram::setUniform(const char *name, float x, float y, float z)
{
   GLint location = getUniformLocation(name);
   glUniform3f(location, x, y, z);
}

void GLSLProgram::setUniform(const char *name, float f)
{
   GLint location = getUniformLocation(name);
   glUniform1f(location, f);
}

void GLSLProgram::setUniform(const char *name, const glm::vec4 &v)
{
   GLint location = getUniformLocation(name);
   glUniform4f(location, v.x, v.y, v.z, v.w);
}
