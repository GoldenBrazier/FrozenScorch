#version 330

#define NR_POINT_LIGHTS 4

in vec3 position;
in vec2 tex_coord;
in vec3 normal;

uniform mat4 g_transform;
uniform mat4 g_perspective;
uniform mat4 g_viewMatrix;

uniform vec3 g_light_position[NR_POINT_LIGHTS];
uniform vec3 g_camera_position;

out vec2 v_tex_coords0;
out vec3 world_normal;
out vec3 world_position_to_light_vec[NR_POINT_LIGHTS];
out vec3 world_position_to_camera_position;

void main()
{
    // calculate position of the vertex in the world
    vec4 world_position = g_transform * vec4(position, 1.0);

    // calculate position of the vertex normal in the world
    world_normal = (g_transform * vec4(normal, 0.0)).xyz;

    // calculate to light vector for each light
    for (int i = 0; i < NR_POINT_LIGHTS; i++) {
        world_position_to_light_vec[i] = g_light_position[i] - world_position.xyz;
    }

    gl_Position = g_perspective * g_viewMatrix * world_position;
    world_position_to_camera_position = g_camera_position - world_position.xyz;
    v_tex_coords0 = tex_coord;
}