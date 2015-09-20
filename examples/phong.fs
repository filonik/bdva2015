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

vec3 shade_phong(Material material, Light light, vec3 E, vec3 N) {
    vec3 result = (light.ambient * get_ambient(material, gs.color));
    
    vec3 L = normalize(light.position.xyz);

    float lambertTerm = dot(N, L);
    
    if (lambertTerm > 0.0) {
        result += (light.diffuse * get_diffuse(material, gs.color)) * lambertTerm;
        
        vec3 R = reflect(-L, N);
        
        float specularTerm = pow(max(dot(R, -E), 0.0), material.shininess);
        
        result += (light.specular * get_specular(material, vec4(1.0))) * specularTerm;
    }

    return result;
}

vec4 get_phong_color(Material material, vec4 tex_coord, vec4 color) {
    vec3 result = vec3(0.0);
    
    vec3 position = (gs.position - inverse_view[3]).xyz;
    vec3 normal = gl_FrontFacing? -gs.transform[2].xyz: +gs.transform[2].xyz;
    
    vec3 E = normalize(position);
    vec3 N = normalize(-normal);
    
    for (int j=0; j<GLANCE_LIGHT_COUNT; ++j) {
        result += shade_phong(material, lights[j], E, N);
    }
    
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
    frag_color = get_phong_color(materials[i], gs.tex_coord, gs.color);
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
