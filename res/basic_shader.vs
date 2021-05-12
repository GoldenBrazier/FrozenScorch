#version 120

attribute vec3 position;

uniform float gScale;
uniform mat4 gTranslation;
uniform mat4 gRotation;

void main()
{
	gl_Position = gTranslation * gRotation * vec4(position * gScale, 1.0);
}