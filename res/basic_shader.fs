#version 120

varying vec2 v_tex_coords0;

uniform sampler2D g_sampler;

void main()
{
	gl_FragColor = texture2D(g_sampler, v_tex_coords0.st);
}