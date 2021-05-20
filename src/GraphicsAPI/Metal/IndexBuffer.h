#pragma once

#include <GraphicsAPI/Generic/IndexBuffer.h>
#include <Utils.h>
#include <mtlpp/mtlpp.hpp>

namespace Metal {

class IndexBuffer : public Generic::IndexBuffer {
    CONSTRUCTIBLE(IndexBuffer)
public:
    IndexBuffer(const void* data, size_t count);

public:
    inline size_t count() const { return m_count; }
    inline MTL::Buffer& buffer() { return m_buffer; }

private:
    size_t m_count;
    MTL::Buffer m_buffer;
};

}