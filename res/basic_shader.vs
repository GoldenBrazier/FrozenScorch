#version 120

attribute vec3 position;

uniform float gScale;
uniform mat4 gTranslation;
uniform mat4 gRotation;
uniform mat4 gPerspective;
varying vec4 Color;

void main()
{
	mat4 trans = gPerspective * gTranslation * gRotation;
	gl_Position = trans * vec4(position * gScale, 1.0);
	Color = vec4(clamp(position, 0.0, 1.0), 1.0);
}