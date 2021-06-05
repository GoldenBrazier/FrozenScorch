#version 120

#define NR_POINT_LIGHTS 4

attribute vec3 position;
attribute vec2 tex_coord;
attribute vec3 normal;

uniform float g_scale;
uniform mat4 g_translation;
uniform mat4 g_rotation;
uniform mat4 g_perspective;
uniform mat4 g_viewMatrix;

uniform vec3 g_light_position[NR_POINT_LIGHTS];
uniform vec3 g_camera_position;

varying vec2 v_tex_coords0;
varying vec3 world_normal;
varying vec3 world_position_to_light_vec[NR_POINT_LIGHTS];
varying vec3 world_position_to_camera_position;

void main()
{
    // calculate transformation matrix for a vertex
    mat4 world_transformation = g_translation * g_rotation;

    // calculate position of the vertex in the world
    vec4 world_position = world_transformation * vec4(position * g_scale, 1.0);

    // calculate position of the vertex normal in the world
    world_normal = (world_transformation * vec4(normal, 0.0)).xyz;

    // calculate to light vector for each light
    for (int i = 0; i < NR_POINT_LIGHTS; i++) {
        world_position_to_light_vec[i] = g_light_position[i] - world_position.xyz;
    }

    gl_Position = g_perspective * g_viewMatrix * world_position;
    world_position_to_camera_position = g_camera_position - world_position.xyz;
    v_tex_coords0 = tex_coord;
}