#pragma once

#include <GL/glew.h>
#include <IndexBuffer.h>
#include <Utils.h>
#include <memory>
#include <stdint.h>
#include <vector>

class VertexBuffer;

class VertexArray final {
    CONSTRUCTIBLE(VertexArray)
public:
    ~VertexArray();

public:
    void bind();
    std::shared_ptr<VertexBuffer> construct_vertex_buffer(const void* data, uint32_t size);
    void set_index_buffer(const std::shared_ptr<IndexBuffer>& index_buffer);

public:
    inline const auto& index_buffer() const { return m_index_buffer; }

private:
    VertexArray();

private:
    GLuint m_id;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers {};
    std::shared_ptr<IndexBuffer> m_index_buffer;
};