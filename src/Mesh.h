#pragma once

#include <GL/glew.h>
#include <GraphicsAPI/Generic/VertexArray.h>
#include <Math/Vector3f.h>
#include <array>
#include <memory>
#include <vector>

class Mesh {
public:
    Mesh(const std::shared_ptr<Generic::VertexArray>& va)
        : m_vertex_array(va)
    {
    }

public:
    void draw();

private:
    std::shared_ptr<Generic::VertexArray> m_vertex_array;
};