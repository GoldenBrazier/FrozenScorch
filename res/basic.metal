#include <metal_stdlib>
using namespace metal;

struct VertUniforms {
    float scale;
    float4x4 rot;
    float4x4 trans;
    float4x4 perspective;
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
    float4x4 adj = float4x4(1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 0.5, 0.5,
                            0.0, 0.0, 0.0, 1.0);

    float3 in = vertex_array[v_id];
    VertexOut out;
    
    float4x4 perspective = uniforms.perspective * adj;
    float4x4 trans = uniforms.rot * uniforms.trans * perspective;
    out.position = float4(in * uniforms.scale, 1.0) * (trans);
    out.color = float4(clamp(in, 0, 1), 1.0);
    return out;
}

fragment float4 frag_func(VertexOut color_out [[stage_in]])
{
    return float4(color_out.color);
}