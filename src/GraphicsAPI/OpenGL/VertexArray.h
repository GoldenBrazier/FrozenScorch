#pragma once

#include <GL/glew.h>
#include <GraphicsAPI/Generic/VertexArray.h>
#include <GraphicsAPI/OpenGL/IndexBuffer.h>
#include <Utils.h>
#include <cstdint>
#include <memory>
#include <vector>

namespace GL {

class VertexBuffer;

class VertexArray : public Generic::VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void bind() override;
    std::shared_ptr<Generic::VertexBuffer> construct_vertex_buffer(const void* data, size_t count) override;
    std::shared_ptr<Generic::IndexBuffer> construct_index_buffer(const void* data, size_t count) override;

    // std::shared_ptr<Generic::VertexBuffer> vertex_buffer(size_t at) override { return m_vertex_buffers[at]; }
    std::shared_ptr<Generic::IndexBuffer> index_buffer() override { return m_index_buffer; }

private:
    GLuint m_id;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers {};
    std::shared_ptr<IndexBuffer> m_index_buffer;
};

}