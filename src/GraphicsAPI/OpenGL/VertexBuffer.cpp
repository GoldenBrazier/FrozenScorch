#include "VertexBuffer.h"
#include <GL/glew.h>
#include <GraphicsAPI/OpenGL/VertexArray.h>
#include <memory>
#include <stdint.h>

namespace GL {

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

void VertexBuffer::register_attribute_vec3(int index, int stride, size_t offset)
{
    auto gl_type = GL::get_type<GL::VarTypes::Vec3>();
    auto gl_dims = GL::get_dims<GL::VarTypes::Vec3>();

    m_vertex_array->bind();

    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, gl_dims, gl_type, false, stride, (void*)offset);
}

void VertexBuffer::register_attribute_vec2(int index, int stride, size_t offset)
{
    auto gl_type = GL::get_type<GL::VarTypes::Vec2>();
    auto gl_dims = GL::get_dims<GL::VarTypes::Vec2>();

    m_vertex_array->bind();

    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, gl_dims, gl_type, false, stride, (void*)offset);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

}