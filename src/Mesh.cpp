#include <GL/glew.h>
#include <Mesh.h>
#include <VertexBuffer.h>

#include <iostream>

void Mesh::draw()
{
    m_vertex_array->bind();
    m_vertex_array->index_buffer()->bind();

    glDrawElements(GL_TRIANGLES, m_vertex_array->index_buffer()->count(), GL_UNSIGNED_INT, nullptr);
}