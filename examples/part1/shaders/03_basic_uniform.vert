#version 440

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexColour;

uniform mat4 RotationMatrix;
            
out vec3 Colour;

void main()
{
   Colour = VertexColour;
   gl_Position = RotationMatrix * vec4(VertexPosition, 1.0);
}

