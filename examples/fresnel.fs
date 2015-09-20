#version 440 core

in VertexData { vec4 position; vec4 tex_coord; vec4 color; mat4 transform; } gs;

#if defined(GLANCE_DEBUG)
in DebugData { vec3 triangle_distance; } gs_debug;
#endif

#include "common.glsl"
#include "materials.glsl"

uniform Material materials[GLANCE_MATERIAL_COUNT];
uniform Light lights[GLANCE_LIGHT_COUNT];

out vec4 frag_color;

const float Air = 1.0;
const float Glass = 1.5; //1.51714;
const float Eta = Air / Glass;

// see http://en.wikipedia.org/wiki/Refractive_index Reflectivity
const float R0 = ((Air - Glass) * (Air - Glass)) / ((Air + Glass) * (Air + Glass));

vec4 get_fresnel_color(Material material, vec4 tex_coord, vec4 color)
{
    vec3 reflection_tex_coord = reflect(E, N);
    vec3 reflection_color = texture(environment, normalize(reflection_tex_coord)).rgb;
    
    vec3 refraction_tex_coord = refract(E, N, Eta);
    vec3 refraction_color = texture(environment, normalize(refraction_tex_coord)).rgb; 

    // see http://en.wikipedia.org/wiki/Schlick%27s_approximation
    float fresnel = R0 + (1.0 - R0) * pow((1.0 - dot(-E, N)), 5.0);
    
    vec3 result = mix(refraction_color, reflection_color, fresnel);
    
    return vec4(result, material.opacity);
}

float edge_intensity(vec3 distance) {
    //float intensity = smoothstep(0.0, 0.1, minimum(distance));
    float intensity = minimum(smoothstep(vec3(0.0), fwidth(distance), distance));
    intensity = 1.0 - clamp(intensity, 0.0, 1.0);
    return intensity;
}

void main()
{
#if GLANCE_MATERIAL_SIDES == 2
    int i = gl_FrontFacing? 0: 1;
#else
    int i = 0;
#endif

#if GLANCE_MATERIAL_SHADE == 1
    frag_color = get_fresnel_color(materials[i], gs.tex_coord, gs.color);
#else
    frag_color = get_material_component(materials[i], gs.tex_coord, gs.color);
#endif

#if defined(GLANCE_DEBUG)
    frag_color = mix(frag_color, vec4(0,0,0,1), edge_intensity(gs_debug.triangle_distance));
#endif

#if GLANCE_ALPHA_TEST
    if (frag_color.a < 0.1) discard;
#endif
}
