#pragma once

#include <GL/glew.h>
#include <GraphicsAPI/OpenGL/VarTypes.h>
#include <GraphicsAPI/Var.h>
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
    template <GL::VarTypes T>
    inline void register_attribute(int index, bool do_transpose, int stride, std::size_t offset)
    {
        auto gl_type = GL::get_type<T>();
        auto gl_dims = GL::get_dims<T>();

        m_vertex_array->bind();

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