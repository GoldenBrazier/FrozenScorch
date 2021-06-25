#pragma once
#include <GL/glew.h>
#include <GraphicsAPI/Generic/ShaderVars.h>
#include <GraphicsAPI/Generic/VertexBuffer.h>
#include <GraphicsAPI/OpenGL/VarTypes.h>
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

    inline const std::vector<Generic::Vertex>& verteces() const override { return m_verteces; }
    void register_attribute_vec2(int index, int stride, size_t offset) override;
    void register_attribute_vec3(int index, int stride, size_t offset) override;
    void bind();

private:
    VertexBuffer(std::vector<Generic::Vertex>&& data, VertexArray* va);

    std::vector<Generic::Vertex> m_verteces;
    uint32_t m_id;
    VertexArray* m_vertex_array;
};

}