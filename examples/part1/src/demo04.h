#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
using namespace glm;

#include "scene-3ds.h"

GLSLProgram program_demo;
GLSLProgram prog_demo03b;

GLuint vao_demo;

void init_demo()
{
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	program_demo.compileShaderFromPath("../../part2/noop.vs");
	program_demo.compileShaderFromPath("../../part2/quad_0.gs");
	program_demo.compileShaderFromPath("../../part2/basic.fs", {});

	//program_demo.compileShaderFromFile("../shaders/phong.vert", GLSLProgram::VERTEX);
	//program_demo.compileShaderFromFile("../shaders/phong.frag", GLSLProgram::FRAGMENT);
	//program_demo.bindAttribLocation(0, "VertexPosition");
	//program_demo.bindAttribLocation(1, "VertexNormal");

	program_demo.link();
	program_demo.use();

	// create and bind vertex array objects = store relationship between buffers and input attributes
	glGenVertexArrays(1, &vao_demo);
}

void render_demo()
{
	program_demo.use();
	program_demo.setUniform("materials[0].colors.ambient", 0.9f, 0.5f, 0.3f);
	program_demo.setUniform("materials[0].colors.diffuse", 0.9f, 0.5f, 0.3f);
	program_demo.setUniform("materials[0].colors.specular", 0.9f, 0.5f, 0.3f);
	program_demo.setUniform("materials[0].colors.emissive", 0.9f, 0.5f, 0.3f);

	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	//glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(90.0f, (GLfloat)800.0f / 600.0f, 0.10f, 1000.0f);
	program_demo.setUniform("Light.Position", view*glm::vec4(0.0f, 0.0f, 2.0f, 1.0f));
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 model_view = view * model;
	glm::mat4 view_projection = projection * view;
	glm::mat4 model_view_projection = projection*model_view;

	program_demo.setUniform("model", model);
	program_demo.setUniform("view", view);
	program_demo.setUniform("model_view", model_view);
	program_demo.setUniform("view_projection", view_projection);
	program_demo.setUniform("model_view_projection", model_view_projection);

	glBindVertexArray(vao_demo);
	glDrawArrays(GL_POINTS, 0, 1);
	program_demo.unUse();
}

