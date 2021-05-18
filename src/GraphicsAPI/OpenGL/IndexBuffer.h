#pragma once
#include <GraphicsAPI/Generic/IndexBuffer.h>
#include <Utils.h>
#include <cstdint>

namespace GL {

class IndexBuffer : public Generic::IndexBuffer {
    CONSTRUCTIBLE(IndexBuffer)
public:
    IndexBuffer(const void* data, size_t count);
    ~IndexBuffer();

    void bind() override;
    inline size_t count() const override { return m_count; }

private:
    uint32_t m_id;
    size_t m_count;
};

}