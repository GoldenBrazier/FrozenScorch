#pragma once
#include <Utils.h>
#include <stdint.h>

class IndexBuffer {
    CONSTRUCTIBLE(IndexBuffer);

public:
    IndexBuffer(const void* data, uint32_t count);
    ~IndexBuffer();

public:
    void bind();

public:
    inline uint32_t count() const { return m_count; }

private:
    uint32_t m_id;
    uint32_t m_count;
};