#pragma once
#include <simd/simd.h>

namespace BasicShader {
using simd::float3;
using simd::float4x4;

#define NR_POINT_LIGHTS 4

struct Uniforms {
    float4x4 rot;
    float4x4 trans;
    float4x4 perspective;
    float4x4 view_matrix;
    float3 camera_position;
    float3 light_position[NR_POINT_LIGHTS];
    float3 light_color[NR_POINT_LIGHTS];
    float3 light_attenuation[NR_POINT_LIGHTS];
    float ambient_brightness;
    float scale;
};

}