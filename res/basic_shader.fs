#version 330

#define NR_POINT_LIGHTS 4

in vec2 v_tex_coords0;
in vec3 world_normal;
in vec3 world_position_to_light_vec[NR_POINT_LIGHTS];
in vec3 world_position_to_camera_position;

out vec4 color;

uniform sampler2D g_sampler;
uniform float g_ambient_brightness;
uniform float g_debug_focused;
uniform vec3 g_light_color[NR_POINT_LIGHTS];
uniform vec3 g_light_attenuation[NR_POINT_LIGHTS];

void main()
{
    // normalize varying vectors
    vec3 world_normal_normalized = normalize(world_normal);
    vec3 world_position_to_camera_position_normalized = normalize(world_position_to_camera_position);

    vec3 all_light_color = g_ambient_brightness * vec3(1.0, 1.0, 1.0);
    all_light_color += g_debug_focused * vec3(0.8, 0.1, 0.5);

    for (int i = 0; i < NR_POINT_LIGHTS; i++) {
        // calculate an attenuation
        float distance = length(world_position_to_light_vec[i]);
        float attenuation = 1 / (g_light_attenuation[i].x + (g_light_attenuation[i].y * distance) + (g_light_attenuation[i].z * distance * distance));

        // calculate diffuse brightness
        vec3 world_position_to_light_vec_normalized = normalize(world_position_to_light_vec[i]);
        float diffuse_brightness = max(dot(world_normal_normalized, world_position_to_light_vec_normalized), 0);

        // calculate specular_brightness
        vec3 world_reflected = reflect(-world_position_to_light_vec_normalized, world_normal);
        float specular_brightness = pow(max(dot(world_position_to_camera_position_normalized, world_reflected), 0), 128);

        all_light_color += ((diffuse_brightness + specular_brightness) * g_light_color[i] * attenuation);
    }

    // set output color
	color = vec4(all_light_color,  1.0) * texture(g_sampler, v_tex_coords0.st);
}