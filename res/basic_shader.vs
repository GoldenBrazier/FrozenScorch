#version 120

attribute vec3 position;

uniform float gScale;
uniform mat4 gTranslation;

void main()
{
	gl_Position = gTranslation * vec4(position * gScale, 1.0);
}