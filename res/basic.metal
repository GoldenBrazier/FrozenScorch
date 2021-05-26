#include <metal_stdlib>
using namespace metal;

struct Vertex {
    packed_float3 position;
    packed_float2 tex_coords;
};

struct Uniforms {
    float scale;
    float4x4 rot;
    float4x4 trans;
    float4x4 perspective;
};

struct VertexStageOutput {
    float4 position [[position]];
    float2 tex_coords;
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

    // Metal and OpenGL has diffrent normalized texture coordinates.
    // Metal has (0, 0) to (1, 1), while OpenGL (-1, -1) to (1, 1).
    float2 tex_coords_adj = float2(0.5, 0.5);

    stage_output.tex_coords = (vertex_array[v_id].tex_coords + 1) * tex_coords_adj;

    float3 in = vertex_array[v_id].position;
    float4x4 perspective = uniforms.perspective * perspective_adj;
    float4x4 trans = uniforms.rot * uniforms.trans * perspective;
    stage_output.position = float4(in * uniforms.scale, 1.0) * (trans);
    return stage_output;
}

constexpr sampler textureSampler(mag_filter::linear, min_filter::linear);
fragment float4 frag_func(
    VertexStageOutput stage_input [[stage_in]],
    texture2d<half> colorTexture [[texture(0)]])
{
    const half4 colorSample = colorTexture.sample(textureSampler, stage_input.tex_coords);
    return float4(colorSample);
}