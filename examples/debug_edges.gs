#version 440 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in VertexData { vec4 position; vec4 tex_coord; vec4 color; mat4 transform; } tes[];
out VertexData { vec4 position; vec4 tex_coord; vec4 color; mat4 transform; } gs;

#if defined(GLANCE_DEBUG)
out DebugData { vec3 triangle_distance; } gs_debug;
#endif

#include "common.glsl"
#include "uniforms.glsl"

void make_vertex(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {
    gs.position = position_out(position);
    gs.tex_coord = tex_coord_out(tex_coord);
    gs.color = color_out(color);
    gs.transform = transform;
    gl_Position = view_projection * gs.position;
    EmitVertex();
}

void main() {
    for(int i=0; i<gl_in.length(); ++i) {
        vec4 position = position_in(tes[i].position);
        vec4 tex_coord = tex_coord_in(tes[i].tex_coord);
        vec4 color = color_in(tes[i].color);
        mat4 transform = tes[i].transform;
#if defined(GLANCE_DEBUG)
        gs_debug.triangle_distance = unit3(i);
#endif
        make_vertex(position, tex_coord, color, transform);
    }
    EndPrimitive();
}