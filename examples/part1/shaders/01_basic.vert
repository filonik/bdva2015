#version 440

in vec3 VertexPosition;
in vec3 VertexColour;
            
out vec3 Colour;

void main()
{
   Colour = VertexColour;
   gl_Position = vec4(VertexPosition, 1.0);
}

