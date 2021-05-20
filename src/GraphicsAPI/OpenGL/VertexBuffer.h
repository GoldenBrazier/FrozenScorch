#pragma once
#include <GL/glew.h>
#include <GraphicsAPI/Generic/Var.h>
#include <GraphicsAPI/OpenGL/VarTypes.h>
#include <GraphicsAPI/Generic/VertexBuffer.h>
#include <Utils.h>
#include <memory>
#include <string>
#include <vector>

namespace GL {

class VertexArray;

class VertexBuffer : public Generic::VertexBuffer {
    friend class VertexArray;
    CONSTRUCTIBLE(VertexBuffer);

public:
    ~VertexBuffer();

public:
    void register_attribute_vec3(int index, int stride, size_t offset);
    void bind();

private:
    VertexBuffer(const void* data, uint32_t size, VertexArray* va);

    uint32_t m_id;
    VertexArray* m_vertex_array;
};

}