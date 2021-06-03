#version 120

attribute vec3 position;
attribute vec2 tex_coord;
attribute vec3 normal;

uniform float g_scale;
uniform mat4 g_translation;
uniform mat4 g_rotation;
uniform mat4 g_perspective;
uniform mat4 g_viewMatrix;

uniform vec3 g_light_position;
uniform vec3 g_camera_position;

varying vec2 v_tex_coords0;
varying vec3 world_normal;
varying vec3 world_position_to_light_vec;
varying vec3 world_position_to_camera_position;

void main()
{
    mat4 world_transformation = g_translation * g_rotation;
    vec4 world_position = world_transformation * vec4(position * g_scale, 1.0);

	gl_Position = g_perspective * g_viewMatrix * world_position;

	v_tex_coords0 = tex_coord;

    world_normal = (world_transformation * vec4(normal, 0.0)).xyz;
    world_position_to_light_vec = g_light_position - world_position.xyz;
    world_position_to_camera_position = g_camera_position - world_position.xyz;
}