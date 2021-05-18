#pragma once
#include <cstddef>
#include <cstdint>

namespace Generic {

class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

    virtual void bind() = 0;
    virtual size_t count() const = 0;
};

}