#pragma once

// struct Vertex {

// };

#include "math/Vector3f.h"

#include <GL/glew.h>
#include <array>
#include <vector>

class Mesh {
public:
    Mesh(const std::vector<Vector3f>& vertices);
    ~Mesh();
    void draw();

private:
    enum VertexArrayBuffer {
        Position,
        NumBuffers,
    };
private:
    std::vector<Vector3f> m_vertices {};
    GLuint m_vertex_array_object;
    GLuint m_vertex_arry_buffers[NumBuffers];
    size_t m_draw_count;
};