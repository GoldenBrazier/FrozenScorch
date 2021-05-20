#include <GL/glew.h>
#include <GraphicsAPI/OpenGL/IndexBuffer.h>
#include <GraphicsAPI/OpenGL/VertexArray.h>
#include <GraphicsAPI/OpenGL/VertexBuffer.h>
#include <Utils.h>
#include <iostream>
#include <memory>

namespace GL {

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind()
{
    glBindVertexArray(m_id);
}

std::shared_ptr<Generic::VertexBuffer> VertexArray::construct_vertex_buffer(const void* data, size_t size)
{
    glBindVertexArray(m_id);

    m_vertex_buffer = VertexBuffer::construct(data, size, this);
    return m_vertex_buffer;
}

std::shared_ptr<Generic::IndexBuffer> VertexArray::construct_index_buffer(const void* data, size_t count)
{
    glBindVertexArray(m_id);

    m_index_buffer = IndexBuffer::construct(data, count);
    return m_index_buffer;
}

}