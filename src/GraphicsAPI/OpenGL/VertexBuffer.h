#pragma once

#include <GL/glew.h>
#include <GraphicsAPI/OpenGL/VarTypes.h>
#include <GraphicsAPI/OpenGL/VertexArray.h>
#include <GraphicsAPI/OpenGL/VertexBuffer.h>
#include <GraphicsAPI/Var.h>
#include <Utils.h>
#include <memory>
#include <string>
#include <vector>

namespace GL {

class VertexBuffer : public Generic::VertexBuffer {
    friend class VertexArray;
    CONSTRUCTIBLE(VertexBuffer);

public:
    ~VertexBuffer();

public:
    void register_attribute_vec3(int index, bool do_transpose, int stride, size_t offset) override
    {
        auto gl_type = GL::get_type<GL::VarTypes::Vec3>();
        auto gl_dims = GL::get_dims<GL::VarTypes::Vec3>();

        m_vertex_array->bind();

        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, gl_dims, gl_type, do_transpose, stride, (void*)offset);
    }

    void bind() override;

private:
    VertexBuffer(const void* data, uint32_t size, VertexArray* va);

    uint32_t m_id;
    VertexArray* m_vertex_array;
};

}