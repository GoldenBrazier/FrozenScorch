#include <metal_stdlib>
using namespace metal;

struct Vertex {
    packed_float3 position;
    packed_float2 tex_coords;
    packed_float3 normal;
};

struct Uniforms {
    float4x4 rot;
    float4x4 trans;
    float4x4 perspective;
    float4x4 view_matrix;
    float3 light_position;
    float3 light_color;
    float ambient_brightness;
    float scale;
};

struct VertexStageOutput {
    float4 position [[position]];
    float2 tex_coords;
    float3 world_normal;
    float3 world_position_to_light_vec;
};

vertex VertexStageOutput vert_func(
    const device Vertex* vertex_array [[buffer(0)]],
    unsigned int v_id [[vertex_id]],
    constant Uniforms& uniforms [[buffer(1)]])
{
    VertexStageOutput stage_output;

    // Metal and OpenGL has different NDC, and we fix this in our shader.
    float4x4 perspective_adj = float4x4(1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.5,
        0.0, 0.0, 0.0, 1.0);

    stage_output.tex_coords = vertex_array[v_id].tex_coords;

    float3 in = vertex_array[v_id].position;
    float3 normal = vertex_array[v_id].normal;

    float4x4 world_transformation = uniforms.rot * uniforms.trans;
    float4 world_position = float4(in * uniforms.scale, 1.0) * world_transformation;

    float4x4 perspective = uniforms.view_matrix * uniforms.perspective * perspective_adj;
    stage_output.position = float4(in * uniforms.scale, 1.0) * (perspective);

    stage_output.world_normal = normalize((float4(normal, 0.0) * world_transformation).xyz);
    stage_output.world_position_to_light_vec = uniforms.light_position - world_position.xyz;

    return stage_output;
}

constexpr sampler textureSampler(mag_filter::linear, min_filter::linear);
fragment float4 frag_func(
    VertexStageOutput stage_input [[stage_in]],
    texture2d<half> colorTexture [[texture(0)]],
    constant Uniforms& uniforms [[buffer(1)]])
{
    const half4 color_sample = colorTexture.sample(textureSampler, stage_input.tex_coords);

    const float3 world_position_to_light_normal = normalize(stage_input.world_position_to_light_vec);

    float brightness = max(dot(stage_input.world_normal, world_position_to_light_normal), 0.0);
    brightness += uniforms.ambient_brightness;

    const float4 frag_color = float4(uniforms.light_color * brightness,  1.0) * float4(color_sample);
    return frag_color;
}