#version 120

attribute vec3 position;
uniform float gScale;
void main()
{
	gl_Position = vec4(position * gScale, 1.0);
}