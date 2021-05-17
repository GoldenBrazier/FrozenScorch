#include "VertexBuffer.h"
#include <GL/glew.h>
#include <memory>
#include <stdint.h>

VertexBuffer::VertexBuffer(const void* data, uint32_t size, VertexArray* va)
    : m_vertex_array(va)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}