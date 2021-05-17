#pragma once
#include <GL/glew.h>
#include <Math/Matrix4f.h>
#include <memory>
#include <string>
#include <vector>

namespace GL {

enum VarTypes {
    Float,
    Vec3,
    Mat4,
};

template <GL::VarTypes T>
constexpr uint32_t get_type()
{
    if constexpr (T == GL::VarTypes::Float) {
        return GL_FLOAT;
    } else if constexpr (T == GL::VarTypes::Vec3) {
        return GL_FLOAT;
    } else {
        []<bool flag = false>() { static_assert(flag, "Unknown type"); }
        ();
    }
}

template <GL::VarTypes T>
constexpr uint32_t get_dims()
{
    if constexpr (T == GL::VarTypes::Float) {
        return 1;
    } else if constexpr (T == GL::VarTypes::Vec3) {
        return 3;
    } else {
        []<bool flag = false>() { static_assert(flag, "Unknown type"); }
        ();
    }
}

}
