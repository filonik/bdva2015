#ifndef GLANCE_UNIFORMS_GLSL
#define GLANCE_UNIFORMS_GLSL

uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 projection = mat4(1.0);
uniform mat4 model_view = mat4(1.0);
uniform mat4 view_projection = mat4(1.0);
uniform mat4 model_view_projection = mat4(1.0);
uniform mat4 inverse_model = mat4(1.0);
uniform mat4 inverse_view = mat4(1.0);
uniform mat4 tex_coord_transform = mat4(1.0);
uniform mat4 color_transform = mat4(1.0);

#define GLANCE_SPACE_MODEL 0
#define GLANCE_SPACE_WORLD 1
#define GLANCE_SPACE_VIEW 2

#ifndef GLANCE_SPACE
#define GLANCE_SPACE GLANCE_SPACE_WORLD
#endif

#if GLANCE_SPACE == GLANCE_SPACE_MODEL
vec4 position_in(vec4 position) { return position; }
vec4 position_out(vec4 position) { return model * position; }
#elif GLANCE_SPACE == GLANCE_SPACE_WORLD
vec4 position_in(vec4 position) { return model * position; }
vec4 position_out(vec4 position) { return position; }
#elif GLANCE_SPACE == GLANCE_SPACE_VIEW
vec4 position_in(vec4 position) { return model_view * position; }
vec4 position_out(vec4 position) { return inverse_view * position; }
#endif

vec4 tex_coord_in(vec4 tex_coord) { return tex_coord; }
vec4 tex_coord_out(vec4 tex_coord) { return tex_coord_transform * tex_coord; }
vec4 color_in(vec4 color) { return color; }
vec4 color_out(vec4 color) { return color_transform * color; }

#endif