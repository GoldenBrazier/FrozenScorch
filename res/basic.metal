#include <metal_stdlib>
using namespace metal;

struct VertUniforms {
    float scale;
    float4x4 rot;
    float4x4 trans;
};

struct VertexOut {
    float4 position [[position]];
    float4 color;
};

vertex VertexOut vert_func(
    const device packed_float3* vertex_array [[buffer(0)]],
    unsigned int v_id [[vertex_id]],
    constant VertUniforms& uniforms [[buffer(1)]])
{
    float3 in = vertex_array[v_id];
    VertexOut out;
    out.position = float4(float4(in, 1.0) * uniforms.rot) * uniforms.trans;
    out.color = float4(in.x, in.y, 1.0, 1.0);
    return out;
}

fragment float4 frag_func(VertexOut color_out [[stage_in]])
{
    return float4(color_out.color);
}