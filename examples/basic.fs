#version 440 core

in VertexData { vec4 position; vec4 tex_coord; vec4 color; mat4 transform; } gs;

#if defined(GLANCE_DEBUG)
in DebugData { vec3 triangle_distance; } gs_debug;
#endif

#include "common.glsl"
#include "materials.glsl"

uniform Material materials[GLANCE_MATERIAL_COUNT];

out vec4 frag_color;

float edge_intensity(vec3 distance) {
    //float intensity = smoothstep(0.0, 0.1, minimum(distance));
    float intensity = minimum(smoothstep(vec3(0.0), fwidth(distance), distance));
    intensity = 1.0 - clamp(intensity, 0.0, 1.0);
    return intensity;
}

void main()
{
    frag_color = get_material_component(materials[i], gs.tex_coord, gs.color);

#if defined(GLANCE_DEBUG)
    frag_color = mix(frag_color, vec4(0,0,0,1), edge_intensity(gs_debug.triangle_distance));
#endif

#if GLANCE_ALPHA_TEST
    if (frag_color.a < 0.1) discard;
#endif
}
