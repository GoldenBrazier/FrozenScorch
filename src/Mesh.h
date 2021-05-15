#pragma once

// struct Vertex {

// };

#include <GL/glew.h>
#include <array>
#include <Math/Vector3f.h>
#include <vector>

class Mesh {
public:
    Mesh(const std::vector<Math::Vector3f>& vertices);
    ~Mesh();
    void draw();

private:
    enum VertexArrayBuffer {
        Position,
        NumBuffers,
    };

private:
    std::vector<Math::Vector3f> m_vertices {};
    GLuint m_vertex_array_object;
    GLuint m_vertex_arry_buffers[NumBuffers];
    size_t m_draw_count;
};