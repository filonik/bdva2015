#ifndef GLANCE_MATH_GLSL
#define GLANCE_MATH_GLSL

#define M_PI 3.1415926535897932384626433832795
#define M_EPS 0.0001

#define vec1 float
#define dvec1 double
#define ivec1 int

#define mat1x2 vec2
#define mat1x3 vec3
#define mat1x4 vec4

vec2 unit2(int i)
{
    vec2 result = vec2(0.0);
    result[i] = 1.0;
    return result;
}

vec3 unit3(int i)
{
    vec3 result = vec3(0.0);
    result[i] = 1.0;
    return result;
}

vec4 unit4(int i)
{
    vec4 result = vec4(0.0);
    result[i] = 1.0;
    return result;
}

vec2 cp(vec2 v0) { return vec2(-v0[0], +v0[1]); }
vec3 cp(vec3 v0, vec3 v1) { return cross(v0, v1); }

vec1 minimum(vec2 v) { return min(v.x, v.y); }
vec1 minimum(vec3 v) { return min(min(v.x, v.y), v.z); }
vec1 minimum(vec4 v) { return min(min(min(v.x, v.y), v.z), v.w); }

vec1 maximum(vec2 v) { return max(v.x, v.y); }
vec1 maximum(vec3 v) { return max(max(v.x, v.y), v.z); }
vec1 maximum(vec4 v) { return max(max(max(v.x, v.y), v.z), v.w); }

mat2 basis_from_points(vec2 p0, vec2 p1)
{
    vec2 a = normalize(p1 - p0);
    vec2 n = normalize(cp(a));
    return mat2(a,n);
}

mat3 basis_from_points(vec3 p0, vec3 p1, vec3 p2)
{    
    vec3 a = normalize(p1 - p0);
    vec3 b = normalize(p2 - p0);
    vec3 n = normalize(cp(a, b));
    return mat3(a,b,n);
}

mat4 look_direction(vec3 forward, vec3 up)
{
    vec3 u = normalize(up);
    
    vec3 z = normalize(forward);
    vec3 x = normalize(cp(z,u));
    vec3 y = normalize(cp(x,z));
    
    return mat4(
        +x, 0.0,
        +y, 0.0,
        -z, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

#endif