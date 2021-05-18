#pragma once
#include <cstddef>

namespace Generic {

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual void register_attribute_vec3(int index, bool do_transpose, int stride, size_t offset) = 0;
    virtual void bind() = 0;
};

}