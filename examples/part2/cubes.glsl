#ifndef GLANCE_CUBES_GLSL
#define GLANCE_CUBES_GLSL

const int cube0_vertex_count = 1;
const int cube1_vertex_count = 2;
const int cube2_vertex_count = 4;
const int cube3_vertex_count = 8;

const int cube0_cube0_face_count = 1;
const int cube1_cube0_face_count = 2;
const int cube2_cube0_face_count = 4;
const int cube3_cube0_face_count = 8;

const int cube0_cube1_face_count = 0;
const int cube1_cube1_face_count = 1;
const int cube2_cube1_face_count = 4;
const int cube3_cube1_face_count = 12;

const int cube0_cube2_face_count = 0;
const int cube1_cube2_face_count = 0;
const int cube2_cube2_face_count = 1;
const int cube3_cube2_face_count = 6;

const vec4 cube0_positions[cube0_vertex_count] = vec4[](
    vec4(0.0, 0.0, 0.0, 0.0)
);

const vec4 cube1_positions[cube1_vertex_count] = vec4[](
    vec4(-1.0, 0.0, 0.0, 0.0),
    vec4(+1.0, 0.0, 0.0, 0.0)
);

const vec4 cube2_positions[cube2_vertex_count] = vec4[](
    vec4(-1.0, -1.0, 0.0, 0.0),
    vec4(+1.0, -1.0, 0.0, 0.0),
    vec4(-1.0, +1.0, 0.0, 0.0),
    vec4(+1.0, +1.0, 0.0, 0.0)
);

const vec4 cube3_positions[cube3_vertex_count] = vec4[](
    vec4(-1.0, -1.0, -1.0, 0.0),
    vec4(+1.0, -1.0, -1.0, 0.0),
    vec4(-1.0, +1.0, -1.0, 0.0),
    vec4(+1.0, +1.0, -1.0, 0.0),
    vec4(-1.0, -1.0, +1.0, 0.0),
    vec4(+1.0, -1.0, +1.0, 0.0),
    vec4(-1.0, +1.0, +1.0, 0.0),
    vec4(+1.0, +1.0, +1.0, 0.0)
);

const vec4 cube0_tex_coords[cube0_vertex_count] = vec4[](
    vec4(0.0, 0.0, 0.0, 0.0)
);

const vec4 cube1_tex_coords[cube1_vertex_count] = vec4[](
    vec4(0.0, 0.0, 0.0, 0.0),
    vec4(1.0, 0.0, 0.0, 0.0)
);

const vec4 cube2_tex_coords[cube2_vertex_count] = vec4[](
    vec4(0.0, 0.0, 0.0, 0.0),
    vec4(1.0, 0.0, 0.0, 0.0),
    vec4(0.0, 1.0, 0.0, 0.0),
    vec4(1.0, 1.0, 0.0, 0.0)
);

const vec4 cube3_tex_coords[cube3_vertex_count] = vec4[](
    vec4(0.0, 0.0, 0.0, 0.0),
    vec4(1.0, 0.0, 0.0, 0.0),
    vec4(0.0, 1.0, 0.0, 0.0),
    vec4(1.0, 1.0, 0.0, 0.0),
    vec4(0.0, 0.0, 1.0, 0.0),
    vec4(1.0, 0.0, 1.0, 0.0),
    vec4(0.0, 1.0, 1.0, 0.0),
    vec4(1.0, 1.0, 1.0, 0.0)
);

const int cube0_cube0_faces[cube0_cube0_face_count][cube0_vertex_count] = int[][](
    int[](0)
);

const int cube1_cube0_faces[cube1_cube0_face_count][cube0_vertex_count] = int[][](
    int[](0),
    int[](1)
);

const int cube2_cube0_faces[cube2_cube0_face_count][cube0_vertex_count] = int[][](
    int[](0),
    int[](1),
    int[](2),
    int[](3)
);

const int cube3_cube0_faces[cube3_cube0_face_count][cube0_vertex_count] = int[][](
    int[](0),
    int[](1),
    int[](2),
    int[](3),
    int[](4),
    int[](5),
    int[](6),
    int[](7)
);

const int cube1_cube1_faces[cube1_cube1_face_count][cube1_vertex_count] = int[][](
    int[](0, 1)
);

const int cube2_cube1_faces[cube2_cube1_face_count][cube1_vertex_count] = int[][](
    int[](0, 1),
    int[](3, 2),
    int[](2, 0),
    int[](1, 3)
);

const int cube3_cube1_faces[cube3_cube1_face_count][cube1_vertex_count] = int[][](
    int[](0, 1),
    int[](3, 2),
    int[](4, 5),
    int[](7, 6),
    int[](2, 0),
    int[](1, 3),
    int[](6, 4),
    int[](5, 7),
    int[](0, 4),
    int[](5, 1),
    int[](2, 6),
    int[](7, 3)
);

const int cube2_cube2_faces[cube2_cube2_face_count][cube2_vertex_count] = int[][](
    int[](0, 1, 2, 3)
);

const int cube3_cube2_faces[cube3_cube2_face_count][cube2_vertex_count] = int[][](
    int[](1, 0, 3, 2),
    int[](4, 5, 6, 7),
    int[](0, 1, 4, 5),
    int[](3, 2, 7, 6),
    int[](2, 0, 6, 4),
    int[](1, 3, 5, 7)
);

void make_vertex(vec4 position, vec4 tex_coord, vec4 color, mat4 transform);

void make_cube0_cube0(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {
    for(int i=0; i<cube0_cube0_face_count; ++i)
    {
        const int face[cube0_vertex_count] = cube0_cube0_faces[i];
        
        vec4 p0 = transform * cube0_positions[face[0]];
        
        make_vertex(position + p0, tex_coord + vec4(0,0,0,0), color, transform);
        EndPrimitive();
    }
}

void make_cube1_cube0(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {
    for(int i=0; i<cube1_cube0_face_count; ++i)
    {
        const int face[cube0_vertex_count] = cube1_cube0_faces[i];
        
        vec4 p0 = transform * cube1_positions[face[0]];
        
        make_vertex(position + p0, tex_coord + vec4(0,0,0,0), color, transform);
        EndPrimitive();
    }
}

void make_cube2_cube0(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {
    for(int i=0; i<cube2_cube0_face_count; ++i)
    {
        const int face[cube0_vertex_count] = cube2_cube0_faces[i];
        
        vec4 p0 = transform * cube2_positions[face[0]];
        
        make_vertex(position + p0, tex_coord + vec4(0,0,0,0), color, transform);
        EndPrimitive();
    }
}

void make_cube3_cube0(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {
    for(int i=0; i<cube3_cube0_face_count; ++i)
    {
        const int face[cube0_vertex_count] = cube3_cube0_faces[i];
        
        vec4 p0 = transform * cube3_positions[face[0]];
        
        make_vertex(position + p0, tex_coord + vec4(0,0,0,0), color, transform);
        EndPrimitive();
    }
}

void make_cube0_cube1(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {}

void make_cube1_cube1(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {
    for(int i=0; i<cube1_cube1_face_count; ++i)
    {
        const int face[cube1_vertex_count] = cube1_cube1_faces[i];
        
        vec4 p0 = transform * cube1_positions[face[0]];
        vec4 p1 = transform * cube1_positions[face[1]];
        
        make_vertex(position + p0, tex_coord + vec4(0,0,0,0), color, transform);
        make_vertex(position + p1, tex_coord + vec4(1,0,0,0), color, transform);
        EndPrimitive();
    }
}

void make_cube2_cube1(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {
    for(int i=0; i<cube2_cube1_face_count; ++i)
    {
        const int face[cube1_vertex_count] = cube2_cube1_faces[i];
        
        vec4 p0 = transform * cube2_positions[face[0]];
        vec4 p1 = transform * cube2_positions[face[1]];
        
        make_vertex(position + p0, tex_coord + vec4(0,0,0,0), color, transform);
        make_vertex(position + p1, tex_coord + vec4(1,0,0,0), color, transform);
        EndPrimitive();
    }
}

void make_cube3_cube1(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {
    for(int i=0; i<cube3_cube1_face_count; ++i)
    {
        const int face[cube1_vertex_count] = cube3_cube1_faces[i];
        
        vec4 p0 = transform * cube3_positions[face[0]];
        vec4 p1 = transform * cube3_positions[face[1]];
        
        make_vertex(position + p0, tex_coord + vec4(0,0,0,0), color, transform);
        make_vertex(position + p1, tex_coord + vec4(1,0,0,0), color, transform);
        EndPrimitive();
    }
}

void make_cube0_cube2(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {}
void make_cube1_cube2(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {}

void make_cube2_cube2(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {
    for(int i=0; i<cube2_cube2_face_count; ++i)
    {
        const int face[cube2_vertex_count] = cube2_cube2_faces[i];
        
        vec4 p0 = transform * cube2_positions[face[0]];
        vec4 p1 = transform * cube2_positions[face[1]];
        vec4 p2 = transform * cube2_positions[face[2]];
        vec4 p3 = transform * cube2_positions[face[3]];
        
        mat4 dual_transform = mat4(basis_from_points(p0.xyz, p1.xyz, p2.xyz));
        
        make_vertex(position + p0, tex_coord + vec4(0,0,0,0), color, transform);
        make_vertex(position + p1, tex_coord + vec4(1,0,0,0), color, transform);
        make_vertex(position + p2, tex_coord + vec4(0,1,0,0), color, transform);
        make_vertex(position + p3, tex_coord + vec4(1,1,0,0), color, transform);
        EndPrimitive();
    }
}

void make_cube3_cube2(vec4 position, vec4 tex_coord, vec4 color, mat4 transform) {
    for(int i=0; i<cube3_cube2_face_count; ++i)
    {
        const int face[cube2_vertex_count] = cube3_cube2_faces[i];
        
        vec4 p0 = transform * cube3_positions[face[0]];
        vec4 p1 = transform * cube3_positions[face[1]];
        vec4 p2 = transform * cube3_positions[face[2]];
        vec4 p3 = transform * cube3_positions[face[3]];
        
        mat4 dual_transform = mat4(basis_from_points(p0.xyz, p1.xyz, p2.xyz));
        
        make_vertex(position + p0, tex_coord + vec4(0,0,0,0), color, transform);
        make_vertex(position + p1, tex_coord + vec4(1,0,0,0), color, transform);
        make_vertex(position + p2, tex_coord + vec4(0,1,0,0), color, transform);
        make_vertex(position + p3, tex_coord + vec4(1,1,0,0), color, transform);
        EndPrimitive();
    }
}

#endif