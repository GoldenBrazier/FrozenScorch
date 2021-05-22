#pragma once
#include <Math/Numbers.h>

namespace Math {

inline float deg_to_rad(float deg)
{
    return deg * Numbers::pi_v<float> / 180.0;
}

};