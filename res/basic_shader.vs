#version 120

attribute vec3 position;

uniform float gScale;
uniform mat4 gTranslation;
uniform mat4 gRotation;
varying vec4 Color;

void main()
{
	gl_Position = gTranslation * gRotation * vec4(position * gScale, 1.0);
	Color = vec4(clamp(position, 0.0, 1.0), 1.0);
}