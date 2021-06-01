#pragma once
#include <Math/Vector2f.h>
#include <Math/Vector3f.h>
#include <Utils.h>
#include <cstddef>
#include <memory>

namespace Generic {

struct PACKED Vertex {
    Math::Vector3f position;
    Math::Vector2f tex_coord;
    Math::Vector3f normal;
};

}