#pragma once
#include <simd/simd.h>

namespace BasicShader {
using simd::float3;
using simd::float4x4;

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

}