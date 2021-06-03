#version 120

varying vec2 v_tex_coords0;
varying vec3 world_normal;
varying vec3 world_position_to_light_vec;
varying vec3 world_position_to_camera_position;

uniform sampler2D g_sampler;
uniform float g_ambient_brightness;
uniform vec3 g_light_color;

void main()
{
    // normalize varying vectors
    vec3 world_normal_normalized = normalize(world_normal);
    vec3 world_position_to_light_vec_normalized = normalize(world_position_to_light_vec);
    vec3 world_position_to_camera_position_normalized = normalize(world_position_to_camera_position);

    // calculate diffuse brightness
    float diffuse_brightness = max(dot(world_normal_normalized, world_position_to_light_vec_normalized), 0);

    // calculate specular_brightness
    vec3 world_reflected = reflect(-world_position_to_light_vec_normalized, world_normal_normalized);
    float specular_brightness = pow(max(dot(world_position_to_camera_position_normalized, world_reflected), 0), 128);

    // calculate overall brightness
    float brightness = g_ambient_brightness + diffuse_brightness + specular_brightness;

    // set output color
	gl_FragColor = vec4(g_light_color * brightness,  1.0) * texture2D(g_sampler, v_tex_coords0.st);
}