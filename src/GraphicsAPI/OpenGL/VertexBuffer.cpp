#include "VertexBuffer.h"
#include <GL/glew.h>
#include <GraphicsAPI/OpenGL/VertexArray.h>
#include <cstdint>
#include <memory>

namespace GL {

VertexBuffer::VertexBuffer(std::vector<Generic::Vertex>&& data, VertexArray* va)
    : m_vertex_array(va)
    , m_verteces(std::move(data))
{
    size_t size = sizeof(std::vector<Generic::Vertex>::value_type) * m_verteces.size();
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, m_verteces.data(), GL_STATIC_DRAW);
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