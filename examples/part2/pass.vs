#version 440 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 tex_coord;
layout(location = 2) in vec4 color;
layout(location = 3) in mat4 transform;

out VertexData { vec4 position; vec4 tex_coord; vec4 color; mat4 transform; } vs;

#include "common.glsl"
#include "uniforms.glsl"

void main()
{
    vs.position = position;
    vs.transform = transform;
    vs.tex_coord = tex_coord;
    vs.color = color;
    gl_Position = model_view_projection * position;
}