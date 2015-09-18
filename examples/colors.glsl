#ifndef GLANCE_COLORS_GLSL
#define GLANCE_COLORS_GLSL

const mat4 gray_scale = mat4(
	0.3, 0.6, 0.1, 0.0,
	0.3, 0.6, 0.1, 0.0,
	0.3, 0.6, 0.1, 0.0,
	0.0, 0.0, 0.0, 1.0
);

const mat4 sepia_tone = mat4(
	0.5, 0.4, 0.2, 0.0,
	0.4, 0.3, 0.2, 0.0,
	0.3, 0.3, 0.1, 0.0,
	0.0, 0.0, 0.0, 1.0
);

vec4 color_from_ordinal(int i)
{
    return vec4(((i >> 0) & 1), ((i >> 1) & 1), ((i >> 2) & 1), 1.0);
}

#endif