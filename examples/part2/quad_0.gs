#version 440 core

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

out VertexData { vec4 position; vec4 tex_coord; vec4 color; } gs;

#include "common.glsl"
#include "uniforms.glsl"

void make_vertex(vec4 position, vec4 tex_coord, vec4 color) {
    gs.position = model * position;
    gs.tex_coord = tex_coord_transform * tex_coord;
    gs.color = color_transform * color;
    gl_Position = view_projection * gs.position;
    EmitVertex();
}

void make_quad(vec4 position, vec4 tex_coord, vec4 color) {
    make_vertex(position + vec4(-1,-1,0,0), tex_coord + vec4(0,0,0,0), color);
    make_vertex(position + vec4(+1,-1,0,0), tex_coord + vec4(1,0,0,0), color);
    make_vertex(position + vec4(-1,+1,0,0), tex_coord + vec4(0,1,0,0), color);
    make_vertex(position + vec4(+1,+1,0,0), tex_coord + vec4(1,1,0,0), color);
    EndPrimitive();
}

void main() {
    make_quad(vec4(0,0,0,1), vec4(0,0,0,1), vec4(1));
}