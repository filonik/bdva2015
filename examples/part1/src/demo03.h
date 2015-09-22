#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
using namespace glm;

#include "scene-3ds.h"

GLSLProgram program_demo;
GLSLProgram prog_demo03b;

float rot3;
Scene3DS scena3;

void init_demo()
{
   rot3 = 0.0f;

   glEnable(GL_DEPTH_TEST); // enable depth-testing
   glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
   
   scena3.load3ds("../obj/teapot.3ds");
   
   program_demo.compileShaderFromFile("../shaders/phong.vert", GLSLProgram::VERTEX);
   program_demo.compileShaderFromFile("../shaders/phong.frag", GLSLProgram::FRAGMENT);
   program_demo.bindAttribLocation(0, "VertexPosition");
   program_demo.bindAttribLocation(1, "VertexNormal");
   program_demo.link();
   program_demo.use();
}


void render_demo()
{
   rot3 += 0.01f;
   
   program_demo.use();
   program_demo.setUniform("Material.Kd", 0.9f, 0.5f, 0.3f);
   program_demo.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
   program_demo.setUniform("Material.Ka", 0.9f, 0.5f, 0.3f);
   program_demo.setUniform("Light.La", 0.4f, 0.4f, 0.4f);
   program_demo.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
   program_demo.setUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
   program_demo.setUniform("Material.Shininess", 10.0f);
   glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
   //glm::mat4 projection = glm::mat4(1.0f);
   glm::mat4 projection = glm::perspective(30.0f, (GLfloat)800.0f/600.0f, 0.10f, 1000.0f);
   program_demo.setUniform("Light.Position", view*glm::vec4(0.0f, 0.0f, 2.0f, 1.0f));
   glm::mat4 model = glm::mat4(1.0f);
   model *= rotate(rot3, vec3(1.0, 0.1, 0.0));
   glm::mat4 mv = view*model;
   program_demo.setUniform("ModelViewMatrix", mv);
   program_demo.setUniform("NormalMatrix", mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
   program_demo.setUniform("MVP", projection*mv);
   scena3.render();
}

