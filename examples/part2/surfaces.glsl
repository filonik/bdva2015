#ifndef GLANCE_SURFACES_GLSL
#define GLANCE_SURFACES_GLSL

#include "math.glsl"

subroutine vec3 ParametricFunction(vec2 coord, vec4 parameters);

subroutine(ParametricFunction)
vec3 PlaneSurface(vec2 coord, vec4 parameters) {
    return vec3(coord, 0.0);
}

subroutine(ParametricFunction)
vec3 SphereSurface(vec2 coord, vec4 parameters) {
    float u = M_PI * coord.s, v = M_PI/2 * coord.t;
    
    float R = parameters.x;
    
    float x = R * sin(u)*cos(v);
    float y = R * sin(v);
    float z = R * cos(u)*cos(v);
    
    return vec3(x, y, z);
}

subroutine(ParametricFunction)
vec3 TorusSurface(vec2 coord, vec4 parameters) {
    float u = coord.s * M_PI, v = coord.t * M_PI;
    
    float R = parameters.x;
    float r = parameters.y;
    
    float x = (-R - r*sin(v))*sin(u);
    float y = (-R - r*sin(v))*cos(u);
    float z = r*cos(v);
    
    return vec3(x, y, z);
}

subroutine(ParametricFunction)
vec3 SuperellipseTorusSurface(vec2 coord, vec4 parameters) {
    float u = coord.s * M_PI, v = coord.t * M_PI;
    
    float R = parameters.x;
    
    float x = (1.0*R + 0.5*pow(abs(sin(v)), 2/n)*sign(sin(v)))*sin(u);
    float y = (1.0*R + 0.5*pow(abs(sin(v)), 2/n)*sign(sin(v)))*cos(u);
    float z = 0.5*pow(abs(cos(v)), 2/n)*sign(cos(v));
    
    return vec3(x, y, z);
}

subroutine(ParametricFunction)
vec3 SuperellipseMobiusSurface(vec2 coord, vec4 parameters) {
    float u = (coord.s + 1.0) * M_PI, v = (coord.t + 1.0) * M_PI;
    
    float R = parameters.x;
    
    float x = (1.0*R + 0.125*sin(u/2)*pow(abs(sin(v)), 2/n)*sign(sin(v)) + 0.5*cos(u/2)*pow(abs(cos(v)), 2/n)*sign(cos(v)))*cos(u);
    float y = (1.0*R + 0.125*sin(u/2)*pow(abs(sin(v)), 2/n)*sign(sin(v)) + 0.5*cos(u/2)*pow(abs(cos(v)), 2/n)*sign(cos(v)))*sin(u);
    float z = -0.5*sin(u/2)*pow(abs(cos(v)), 2/n)*sign(cos(v)) + 0.125*cos(u/2)*pow(abs(sin(v)), 2/n)*sign(sin(v));
    return vec3(x, y, z);
}

subroutine(ParametricFunction)
vec3 HelicoidSurface(vec2 coord, vec4 parameters) {
    const float n = 2.0;
    
    float u = coord.s, v = M_PI/2 * coord.t;
    
    float R = parameters.x;
    float h = parameters.w;
    float f = parameters.w * n;
    
    return vec3(R*u*cos(f*v), R*u*sin(f*v), h*v);
}

subroutine(ParametricFunction)
vec3 SpiralSurface(vec2 coord, vec4 parameters) {
    const float Alpha = 0.3;

    float u = (coord.s + 1.0) * M_PI, v = (coord.t + 1.0) * M_PI;
    
    float x = Alpha*(-v/(2*M_PI) + 1)*(cos(u) + 1)*cos(2*v) + 0.1*cos(2*v);
    float y = Alpha*(-v/(2*M_PI) + 1)*(cos(u) + 1)*sin(2*v) + 0.1*sin(2*v);
    float z = Alpha*(-v/(2*M_PI) + 1)*sin(u) + v/(2*M_PI);
    
    return 2 * vec3(x, y, -z);
}

subroutine(ParametricFunction)
vec3 KleinSurface(vec2 coord, vec4 parameters) {
    float u = (coord.s + 1.0) * M_PI, v = (coord.t + 1.0) * M_PI;
    
    float x = 0.0f;
    float y = 0.0f;
    
    if (u < M_PI)
    {
        x = 3 * cos(u) * (1 + sin(u)) + (2 * (1 - cos(u) / 2)) * cos(u) * cos(v);
        y = -8 * sin(u) - 2 * (1 - cos(u) / 2) * sin(u) * cos(v);
    }
    else
    {
        x = 3 * cos(u) * (1 + sin(u)) + (2 * (1 - cos(u) / 2)) * cos(v + M_PI);
        y = -8 * sin(u);
    }

    float z = -2 * (1 - cos(u) / 2) * sin(v);
    
    return vec3(x, y, z) * 0.125;
}

#endif