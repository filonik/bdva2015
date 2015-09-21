#ifndef GLANCE_MATERIALS_GLSL
#define GLANCE_MATERIALS_GLSL

#ifndef GLANCE_MATERIAL_SIDES
#define GLANCE_MATERIAL_SIDES 1
#endif

#ifndef GLANCE_MATERIAL_COUNT
#define GLANCE_MATERIAL_COUNT GLANCE_MATERIAL_SIDES
#endif

#if defined(GLANCE_MATERIAL_AMBIENT_COLOR) || defined(GLANCE_MATERIAL_DIFFUSE_COLOR) || defined(GLANCE_MATERIAL_SPECULAR_COLOR) || defined(GLANCE_MATERIAL_EMISSIVE_COLOR) || defined(GLANCE_MATERIAL_VERTEX_COLOR)
#define GLANCE_MATERIAL_COLOR
#endif

#if defined(GLANCE_MATERIAL_AMBIENT_TEXTURE) || defined(GLANCE_MATERIAL_DIFFUSE_TEXTURE)
#define GLANCE_MATERIAL_TEXTURE
#endif

struct Colors
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emissive;
};

struct Textures
{
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emissive;
};

struct Material
{
    Colors colors;
    Textures textures;
    
    float opacity;
    float shininess;
    float reflectiveness;
    float refractiveness;
};

vec3 get_ambient(Material material, vec4 color)
{
#if defined(GLANCE_MATERIAL_AMBIENT_COLOR)
	return material.colors.ambient;
#else
	return color.rgb;
#endif
}

vec3 get_diffuse(Material material, vec4 color)
{
#if defined(GLANCE_MATERIAL_DIFFUSE_COLOR)
	return material.colors.diffuse;
#else
	return color.rgb;
#endif
}

vec3 get_specular(Material material, vec4 color)
{
#if defined(GLANCE_MATERIAL_SPECULAR_COLOR)
	return material.colors.specular;
#else
	return color.rgb;
#endif
}

vec3 get_emissive(Material material, vec4 color)
{
#if defined(GLANCE_MATERIAL_EMISSIVE_COLOR)
	return material.colors.emissive;
#else
	return color.rgb;
#endif
}

vec4 get_color_component(Material material, vec4 color)
{
#if defined(GLANCE_MATERIAL_AMBIENT_COLOR) && defined(GLANCE_MATERIAL_DIFFUSE_COLOR)
    return vec4(material.colors.ambient * material.colors.diffuse, material.opacity);
#elif defined(GLANCE_MATERIAL_AMBIENT_COLOR)
    return vec4(material.colors.ambient, material.opacity);
#elif defined(GLANCE_MATERIAL_DIFFUSE_COLOR)
    return vec4(material.colors.diffuse, material.opacity);
#elif defined(GLANCE_MATERIAL_SPECULAR_COLOR)
    return vec4(material.colors.specular, material.opacity);
#elif defined(GLANCE_MATERIAL_EMISSIVE_COLOR)
    return vec4(material.colors.emissive, material.opacity);
#else
    return color;
#endif
}

vec4 get_texture_component(Material material, vec4 tex_coord, vec4 color)
{
#if defined(GLANCE_MATERIAL_AMBIENT_TEXTURE) && defined(GLANCE_MATERIAL_DIFFUSE_TEXTURE)
    return texture(material.textures.ambient, tex_coord.st) * texture(material.textures.diffuse, tex_coord.st);
#elif defined(GLANCE_MATERIAL_AMBIENT_TEXTURE)
    return texture(material.textures.ambient, tex_coord.st);
#elif defined(GLANCE_MATERIAL_DIFFUSE_TEXTURE)
    return texture(material.textures.diffuse, tex_coord.st);
#elif defined(GLANCE_MATERIAL_SPECULAR_TEXTURE)
    return texture(material.textures.specular, tex_coord.st);
#elif defined(GLANCE_MATERIAL_EMISSIVE_TEXTURE)
    return texture(material.textures.emissive, tex_coord.st);
#else
    return color;
#endif
}

vec4 get_material_component(Material material, vec4 tex_coord, vec4 color)
{
#if defined(GLANCE_MATERIAL_TEXTURE) && defined(GLANCE_MATERIAL_COLOR)
    return get_texture_component(material, tex_coord, color) * get_color_component(material, color);
#elif defined(GLANCE_MATERIAL_TEXTURE)
    return get_texture_component(material, tex_coord, color);
#elif defined(GLANCE_MATERIAL_COLOR)
    return get_color_component(material, color);
#else
    return color;
#endif
}

#endif
