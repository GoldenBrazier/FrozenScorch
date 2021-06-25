#include <GL/glew.h>
#include <Mesh.h>

#include <GraphicsAPI/Generic/Constructors.h>
#include <GraphicsAPI/OpenGL/VertexArray.h>
#include <Parsers/ObjParser.h>

Mesh::Mesh(const std::string& obj_path, int position, int tex_coords, int normal)
{
    auto parser = ObjParser(obj_path);
    parser.parse();

    m_vertex_array = Constructors::VertexArray::construct();

    auto vb = m_vertex_array->construct_vertex_buffer(std::move(parser.vertexes()));

    vb->register_attribute_vec3(position, sizeof(Generic::Vertex), 0);
    vb->register_attribute_vec2(tex_coords, sizeof(Generic::Vertex), sizeof(Math::Vector3f));
    vb->register_attribute_vec3(normal, sizeof(Generic::Vertex), sizeof(Math::Vector3f) + sizeof(Math::Vector2f));

    m_vertex_array->construct_index_buffer(parser.indeces().data(), parser.indeces().size());
}

void Mesh::draw() const
{
    auto va_gl = std::static_pointer_cast<GL::VertexArray>(m_vertex_array);
    va_gl->bind();

    glDrawElements(GL_TRIANGLES, va_gl->index_buffer()->count(), GL_UNSIGNED_INT, nullptr);
}
