#version 440

in vec3 Colour;

out vec4 FragmentColuor; 

void main()
{
   FragmentColuor = vec4(Colour, 1.0);
}

