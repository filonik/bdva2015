#version 440 core

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in VertexData { vec4 position; vec4 tex_coord; vec4 color; mat4 transform; } tes[];
out VertexData { vec4 position; vec4 tex_coord; vec4 color; } gs;

#include "common.glsl"
#include "uniforms.glsl"

void make_vertex(vec4 position, vec4 tex_coord, vec4 color) {
	gs.position = position_out(position);
	gs.tex_coord = tex_coord_out(tex_coord);
	gs.color = color_out(color);
	gl_Position = view_projection * gs.position;
	EmitVertex();
}

void make_quad(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {
    make_vertex(position + transform * vec4(-1,-1,0,0), tex_coord + vec4(0,0,0,0), color);
    make_vertex(position + transform * vec4(+1,-1,0,0), tex_coord + vec4(1,0,0,0), color);
    make_vertex(position + transform * vec4(-1,+1,0,0), tex_coord + vec4(0,1,0,0), color);
    make_vertex(position + transform * vec4(+1,+1,0,0), tex_coord + vec4(1,1,0,0), color);
    EndPrimitive();
}

void main() {
    vec4 position = position_in(tes[0].position);
    vec4 tex_coord = tex_coord_in(tes[0].tex_coord);
    vec4 color = color_in(tes[0].color);

    make_quad(position, tex_coord, color, tes[0].transform);
}