#pragma once

#include <simd/simd.h>
using simd::float4x4;

struct VertUniforms {
    float4x4 rot;
    float4x4 trans;
};

struct FragmentUniforms {
    float brightness;
};