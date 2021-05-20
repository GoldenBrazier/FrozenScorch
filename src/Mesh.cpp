#include <GL/glew.h>
#include <Mesh.h>

#include <iostream>

void Mesh::draw()
{
    // m_vertex_array->bind();
    glDrawElements(GL_TRIANGLES, m_vertex_array->index_buffer()->count(), GL_UNSIGNED_INT, nullptr);
}