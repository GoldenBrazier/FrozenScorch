#pragma once
#include <Backend/OpenGL/VarTypes.h>
#include <GL/glew.h>
#include <stdint.h>
#include <type_traits>

namespace GL {

template <typename T>
constexpr uint32_t GetType()
{
    if constexpr (std::is_same<T, float>()) {
        return GL_FLOAT;
    } else if constexpr (std::is_same<T, GL::Vec3>()) {
        return GL_FLOAT;
    } else {
        []<bool flag = false>() { static_assert(flag, "Unknown type"); }
        ();
    }
}

template <typename T>
constexpr uint32_t GetDims()
{
    if constexpr (std::is_same<T, GL::Float>()) {
        return 1;
    } else if constexpr (std::is_same<T, GL::Vec3>()) {
        return 3;
    } else {
        []<bool flag = false>() { static_assert(flag, "Unknown type"); }
        ();
    }
}

}