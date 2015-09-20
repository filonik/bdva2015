#version 440 core

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

out VertexData { vec4 position; vec4 tex_coord; vec4 color; } gs;

#include "common.glsl"
#include "uniforms.glsl"

// Model Space
vec4 position_in(vec4 position) { return position; }
vec4 position_out(vec4 position) { return model * position; }

// World Space
//vec4 position_in(vec4 position) { return model * position; }
//vec4 position_out(vec4 position) { return position; }

// View Space
//vec4 position_in(vec4 position) { return model_view * position; }
//vec4 position_out(vec4 position) { return inverse_view * position; }

vec4 tex_coord_in(vec4 tex_coord) { return tex_coord; }
vec4 tex_coord_out(vec4 tex_coord) { return tex_coord_transform * tex_coord; }

vec4 color_in(vec4 color) { return color; }
vec4 color_out(vec4 color) { return color_transform * color; }

void make_vertex(vec4 position, vec4 tex_coord, vec4 color) {
    gs.position = position_out(position);
    gs.tex_coord = tex_coord_out(tex_coord);
    gs.color = color_out(color);
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
    vec4 position = position_in(vec4(0,0,0,1));
    vec4 tex_coord = tex_coord_in(vec4(0,0,0,1));
    vec4 color = color_in(vec4(1.0));
    
    make_quad(position, tex_coord, color);
}