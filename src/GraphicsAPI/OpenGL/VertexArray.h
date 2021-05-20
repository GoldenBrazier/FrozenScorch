#pragma once
#include <GL/glew.h>
#include <GraphicsAPI/Generic/VertexArray.h>
#include <GraphicsAPI/Generic/VertexBuffer.h>
#include <GraphicsAPI/OpenGL/IndexBuffer.h>
#include <GraphicsAPI/OpenGL/VertexBuffer.h>
#include <Utils.h>
#include <cstdint>
#include <memory>
#include <vector>

namespace GL {

class VertexArray : public Generic::VertexArray {
public:
    VertexArray();
    ~VertexArray();

    std::shared_ptr<Generic::VertexBuffer> construct_vertex_buffer(const void* data, size_t size) override;
    std::shared_ptr<Generic::IndexBuffer> construct_index_buffer(const void* data, size_t count) override;

    std::shared_ptr<Generic::VertexBuffer> vertex_buffer() override { return std::static_pointer_cast<Generic::VertexBuffer>(m_vertex_buffer); }
    std::shared_ptr<Generic::IndexBuffer> index_buffer() override { return m_index_buffer; }

public:
    void bind();

private:
    GLuint m_id;
    std::shared_ptr<VertexBuffer> m_vertex_buffer {};
    std::shared_ptr<IndexBuffer> m_index_buffer {};
};

}