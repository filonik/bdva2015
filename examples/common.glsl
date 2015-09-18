#ifndef GLANCE_COMMON_GLSL
#define GLANCE_COMMON_GLSL

#ifndef GLANCE_CLIP_PLANE_COUNT
#define GLANCE_CLIP_PLANE_COUNT 0
#endif

#ifndef GLANCE_LAYER_COUNT
#define GLANCE_LAYER_COUNT 1
#endif

#ifndef GLANCE_TESS_LEVEL_INNER
#define GLANCE_TESS_LEVEL_INNER 128
#endif

#ifndef GLANCE_TESS_LEVEL_OUTER
#define GLANCE_TESS_LEVEL_OUTER 128
#endif

#include "math.glsl"

vec4 colorFromOrdinal(int i)
{
    return vec4(((i >> 0) & 1), ((i >> 1) & 1), ((i >> 2) & 1), 1.0);
}

#endif
