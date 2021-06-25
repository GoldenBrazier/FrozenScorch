#pragma once

#include <GraphicsAPI/Generic/VertexBuffer.h>
#include <Renderer/Metal/Renderer.h>

#include <Utils.h>
#include <mtlpp/mtlpp.hpp>

namespace Metal {

class VertexBuffer : public Generic::VertexBuffer {
    CONSTRUCTIBLE(VertexBuffer);

public:
    VertexBuffer(std::vector<Generic::Vertex>&&);

    inline const std::vector<Generic::Vertex>& verteces() const override { return m_verteces; }
    inline void register_attribute_vec2(int index, int stride, size_t offset) override { index = index, offset = offset; }
    inline void register_attribute_vec3(int index, int stride, size_t offset) override { index = index, offset = offset; }

    MTL::Buffer& buffer() { return m_buffer; }

private:
    std::vector<Generic::Vertex> m_verteces;
    MTL::Buffer m_buffer;
    int index {};
    size_t offset {};
};

}