#ifndef GLANCE_LIGHTS_GLSL
#define GLANCE_LIGHTS_GLSL

#ifndef GLANCE_LIGHT_COUNT
#define GLANCE_LIGHT_COUNT 1
#endif

struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 attenuation;
    vec4 position;
};

#endif