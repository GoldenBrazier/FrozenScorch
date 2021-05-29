#version 120

attribute vec3 position;
attribute vec2 tex_coord;

uniform float g_scale;
uniform mat4 g_translation;
uniform mat4 g_rotation;
uniform mat4 g_perspective;
uniform mat4 g_viewMatrix;

varying vec2 v_tex_coords0;

void main()
{
	mat4 trans = g_perspective * g_viewMatrix * g_translation * g_rotation;
	gl_Position = trans * vec4(position * g_scale, 1.0);
	v_tex_coords0 = tex_coord;
}