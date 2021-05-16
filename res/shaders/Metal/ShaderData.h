#pragma once

#if __METAL_MACOS__ || __METAL_IOS__
#include <metal_stdlib>
using namespace metal;
#else
#include <simd/simd.h>
using simd::float4x4;
#endif /* __METAL_MACOS__ || __METAL_IOS__ */

struct VertUniforms {
    float4x4 rot;
    float4x4 trans;
};

struct FragmentUniforms {
    float brightness;
};