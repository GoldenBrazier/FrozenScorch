#include "VertexArray.h"

#include <GL/glew.h>
#include <Utils.h>
#include <iostream>
#include <memory>
#include <VertexBuffer.h>

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

std::shared_ptr<VertexBuffer> VertexArray::construct_vertex_buffer(const void* data, uint32_t size)
{
    glBindVertexArray(m_id);

    auto vb = VertexBuffer::construct(data, size, this);
    m_vertex_buffers.push_back(vb);
    return vb;
}

void VertexArray::set_index_buffer(const std::shared_ptr<IndexBuffer>& index_buffer)
{
    glBindVertexArray(m_id);
    m_index_buffer = index_buffer;
    m_index_buffer->bind();
}