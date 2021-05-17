#pragma once

#include <GL/glew.h>
#include <Math/Vector3f.h>
#include <VertexArray.h>
#include <array>
#include <memory>
#include <vector>

class Mesh {
public:
    Mesh(const std::shared_ptr<VertexArray>& va)
        : m_vertex_array(va)
    {
    }

public:
    void draw();

private:
    std::shared_ptr<VertexArray> m_vertex_array;
};