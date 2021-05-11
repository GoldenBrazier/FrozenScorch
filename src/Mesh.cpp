#include "Mesh.h"
#include <GL/glew.h>

#include <iostream>

Mesh::Mesh(const std::vector<Vector3f>& vertices)
    : m_vertices(vertices)
{
    std::cout << "cum";
    glGenVertexArrays(1, &m_vertex_array_object);
    glBindVertexArray(m_vertex_array_object);
std::cout << "cum";
    glGenBuffers(NumBuffers, m_vertex_arry_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_arry_buffers[Position]);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertices[0]), m_vertices.data(), GL_STATIC_DRAW);
std::cout << "cum";
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
std::cout << "cum";
    glBindVertexArray(0); 
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertex_array_object);
}

void Mesh::draw()
{
    glBindVertexArray(m_vertex_array_object);

    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

    glBindVertexArray(0); 
}