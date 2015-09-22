#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glsl-program.h"

#define STRINGIFY(A) #A

//#include "demo01.h"
//#include "demo02.h"
 #include "demo03.h"


void displayOpenGLInfo()
{
   // get OpenGL version information
   //
   const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
   const GLubyte* vendor = glGetString(GL_VENDOR); // get vendor string
   const GLubyte* version = glGetString(GL_VERSION); // version as a string
   const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION); // GLSL version as a string
   
   GLint major, minor;
   glGetIntegerv(GL_MAJOR_VERSION, &major);
   glGetIntegerv(GL_MINOR_VERSION, &minor);
   
   std::cout << "GL Vendor: " << vendor << std::endl;
   std::cout << "GL Renderer: " << renderer << std::endl;
   std::cout << "GL Version: " << version << std::endl;
   std::cout << "GL Version: " << major << "." << minor << std::endl;
   std::cout << "GLSL Version: " << glslVersion << std::endl;
   
   // get extensions list
   //
   GLint nExtensions;
   glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
   for (int i=0; i<nExtensions; i++)
   {
      // std::cout << glGetStringi(GL_EXTENSIONS, i) << std::endl;;
   }
}


void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
}


int main()
{
   GLFWwindow* w;

	// Initialize GLFW
	if (!glfwInit())
      return -1;

   // Let's use OpenGL 4.4
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

   // Create a windowed mode window and its OpenGL context 
	w = glfwCreateWindow(640, 480, "BDVA Demo", NULL, NULL);
	if (!w) {
		glfwTerminate();
		return -1;
	}

   glfwSetKeyCallback(w, onKeyPress);

	// Make the window's context current 
	glfwMakeContextCurrent(w);

	// start GLEW extension handler
   glewExperimental = GL_TRUE;
   if (glewInit() != GLEW_OK) {
      glfwTerminate();
      return -1;
   }

	displayOpenGLInfo();

	init_demo();

	// Loop until the user closes the window 
	while (!glfwWindowShouldClose(w))
	{
      glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
      glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render here 
		render_demo();

		// Swap front and back buffers 
		glfwSwapBuffers(w);

		// Poll for and process events 
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}


