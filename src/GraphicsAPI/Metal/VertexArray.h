#pragma once

#include <GraphicsAPI/Generic/VertexArray.h>
#include <GraphicsAPI/Metal/IndexBuffer.h>
#include <GraphicsAPI/Metal/VertexBuffer.h>
#include <Renderer/Metal/Renderer.h>

namespace Metal {

class VertexArray : public Generic::VertexArray {
public:
    VertexArray() = default;

public:
    std::shared_ptr<Generic::VertexBuffer> construct_vertex_buffer(const void* data, size_t size) override;
    inline std::shared_ptr<Generic::VertexBuffer> vertex_buffer() override { return m_vertex_buffer; }
    inline std::shared_ptr<Generic::IndexBuffer> index_buffer() override { return m_index_buffer; }
    inline std::shared_ptr<Generic::IndexBuffer> construct_index_buffer(const void* data, size_t count) override
    {
        m_index_buffer = IndexBuffer::construct(data, count);
        return m_index_buffer;
    }

private:
    std::shared_ptr<Metal::Renderer> m_renderer {};
    std::shared_ptr<Metal::VertexBuffer> m_vertex_buffer {};
    std::shared_ptr<Metal::IndexBuffer> m_index_buffer {};
};

}