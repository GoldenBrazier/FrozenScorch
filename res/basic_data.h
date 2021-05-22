#pragma once
#include <simd/simd.h>

namespace BasicShader {
using simd::float4x4;

struct Uniforms {
    float scale;
    float4x4 rot;
    float4x4 trans;
    float4x4 perspective;
};

}