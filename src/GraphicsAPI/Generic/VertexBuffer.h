#pragma once
#include <cstddef>

namespace Generic {

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual void register_attribute_vec2(int index, int stride, size_t offset) = 0;
    virtual void register_attribute_vec3(int index, int stride, size_t offset) = 0;
};

}