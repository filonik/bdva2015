#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

GLSLProgram program_demo;

float positionData_demo[] = {
   -0.8f, -0.8f, 0.0f,
    0.8f, -0.8f, 0.0f,
    0.0f,  0.8f, 0.0f
};

float colourData_demo[] = {
   1.0f, 0.0f, 0.0f,
   0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 1.0f
};

// vertex array object
GLuint vao_demo;

// buffer objects
GLuint vbo_demo[2];

/////////////////////////////////////////////////////////////////////////////

const std::string vs_demo = STRINGIFY(
   \n#version 440\n

   layout (location=0) in vec3 VertexPosition;
   layout (location=1) in vec3 VertexColour;

   out vec3 Colour;

   uniform mat4 RotationMatrix;

   void main()
   {
      Colour = VertexColour;
      gl_Position = RotationMatrix * vec4(VertexPosition, 1.0);
   }
);

/////////////////////////////////////////////////////////////////////////////

const std::string fs_demo = STRINGIFY(
   \n#version 440\n

   in vec3 Colour;

   layout (location=0) out vec4 FragmentColour;

   void main() {
      FragmentColour = vec4(Colour, 1.0);
   }
);

/////////////////////////////////////////////////////////////////////////////

int init_demo()
{
   program_demo.compileShader(vs_demo, GLSLProgram::VERTEX);
   program_demo.compileShader(fs_demo, GLSLProgram::FRAGMENT);
   
   program_demo.bindAttribLocation(0, "VertexPosition");
   program_demo.bindAttribLocation(1, "VertexColour");
   
   program_demo.link();

   glGenBuffers(2, vbo_demo);
   GLuint posBufferHandle = vbo_demo[0];
   GLuint colBufferHandle = vbo_demo[1];
   
   // populate buffers
   // position
   glBindBuffer(GL_ARRAY_BUFFER, posBufferHandle);
   glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), positionData_demo, GL_STATIC_DRAW);
   // colour
   glBindBuffer(GL_ARRAY_BUFFER, colBufferHandle);
   glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), colourData_demo, GL_STATIC_DRAW);

   // create and bind vertex array objects = store relationship between buffers and input attributes
   glGenVertexArrays(1, &vao_demo);
   glBindVertexArray(vao_demo);

   // enable vertex attribute arrays
   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);

   // map index 0 to position buffer
   glBindBuffer(GL_ARRAY_BUFFER, posBufferHandle);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

   glBindBuffer(GL_ARRAY_BUFFER, colBufferHandle);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

   glBindVertexArray(0);

   return true;
}

float angle = 0.0f;

void render_demo()
{
   program_demo.use();

   glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
   GLuint location = glGetUniformLocation(program_demo.getHandle(), "RotationMatrix");
   if (location >= 0)
      glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);
   angle += 0.025f;

   glBindVertexArray(vao_demo);
   glDrawArrays(GL_TRIANGLES, 0, 3);
   program_demo.unUse();
}


