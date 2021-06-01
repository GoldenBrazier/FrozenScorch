#version 120

varying vec2 v_tex_coords0;
varying vec3 world_normal;
varying vec3 world_position_to_light_vec;

uniform sampler2D g_sampler;
uniform float g_ambient_brightness;
uniform vec3 g_light_color;

void main()
{
    vec3 world_normal_normalized = normalize(world_normal);
    vec3 world_position_to_light_vec_normalized = normalize(world_position_to_light_vec);

    float brightness = max(dot(world_normal_normalized, world_position_to_light_vec_normalized), 0);
    brightness += g_ambient_brightness;

	gl_FragColor = vec4(g_light_color * brightness,  1.0) * texture2D(g_sampler, v_tex_coords0.st);
}