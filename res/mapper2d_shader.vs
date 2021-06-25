#version 330

in vec3 position;
in vec2 tex_coord;
in vec3 normal;

uniform mat4 g_transform;
uniform mat4 g_perspective;
uniform mat4 g_viewMatrix;

void main()
{
    vec4 world_position = g_transform * vec4(position, 1.0);
    gl_Position = g_perspective * g_viewMatrix * world_position;
}