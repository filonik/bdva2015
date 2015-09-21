#version 440 core

#if defined(GLANCE_BACKGROUND_CUBE)
uniform samplerCube background;
#else
uniform sampler2D background;
#endif

in VertexData { vec4 position; vec4 tex_coord; vec4 color; } gs;

out vec4 frag_color;

void main()
{
    frag_color = gs.color * texture(background, gs.tex_coord.xyz);
}