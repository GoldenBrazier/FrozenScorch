#pragma once

#include <Backend/OpenGL/Utils.h>
#include <Backend/Var.h>
#include <GL/glew.h>
#include <Utils.h>
#include <VertexArray.h>
#include <memory>
#include <string>
#include <vector>

class VertexBuffer final {
    friend class VertexArray;
    CONSTRUCTIBLE(VertexBuffer);

public:
    ~VertexBuffer();

public:
    template <typename T>
    inline void register_attribute(const std::shared_ptr<Backend::Attribute>& var, bool do_transpose, int stride, std::size_t offset)
    {
        auto gl_type = GL::GetType<T>();
        auto gl_dims = GL::GetDims<T>();

        m_vertex_array->bind();
        auto index = var->index();

        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, gl_dims, gl_type, do_transpose, stride, (void*)offset);
    }

    void bind();

private:
    VertexBuffer(const void* data, uint32_t size, VertexArray* va);

private:
    uint32_t m_id;
    VertexArray* m_vertex_array;
};