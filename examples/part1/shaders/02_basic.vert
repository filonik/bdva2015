#version 440

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColour;
            
out vec3 Colour;

void main()
{
   Colour = VertexColour;
   gl_Position = vec4(VertexPosition, 1.0);
}

