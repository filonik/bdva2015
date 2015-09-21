#version 440 core

layout(triangles) in;
layout(line_strip, max_vertices=18) out;

in VertexData { vec4 position; vec4 tex_coord; vec4 color; mat4 transform; } tes[];
out VertexData { vec4 position; vec4 tex_coord; vec4 color; } gs;

#include "common.glsl"
#include "uniforms.glsl"

uniform float size = 0.25;

void make_vertex(vec4 position, vec4 tex_coord, vec4 color) {
    gs.position = position;
    gs.tex_coord = tex_coord;
    gs.color = color;
    gl_Position = view_projection * gs.position;
    EmitVertex();
}

void main() {
    for (int i=0; i<gl_in.length(); i++) {
        vec4 position = position_out(position_in(tes[i].position));
        mat4 transform = tes[i].transform;
        
        for (int j=0; j<3; ++j) {
            make_vertex(position + 0.0*size*transform[j], vec4(0,0,0,1), color_from_ordinal(j+1));
            make_vertex(position + 1.0*size*transform[j], vec4(1,0,0,1), color_from_ordinal(j+1));
            EndPrimitive();
        }
    }
}