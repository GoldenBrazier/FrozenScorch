#include "ObjParser.h"

void ObjParser::paste_vertex_to_va(int3 a)
{
    if (m_vertex_to_index.find(a) == m_vertex_to_index.end()) {
        int vertex_index_in_tmp = std::get<0>(a) - 1;
        int tex_index_in_tmp = std::get<1>(a) - 1;
        auto vec3 = Math::Vector3f(std::get<0>(m_tmp_vertex_storage[vertex_index_in_tmp]), std::get<1>(m_tmp_vertex_storage[vertex_index_in_tmp]), std::get<2>(m_tmp_vertex_storage[vertex_index_in_tmp]));
        auto vec2 = Math::Vector2f(std::get<0>(m_tmp_texture_storage[tex_index_in_tmp]), std::get<1>(m_tmp_texture_storage[tex_index_in_tmp]));
        m_vertices.push_back(Generic::Vertex { vec3, vec2 });
        m_vertex_to_index[a] = m_vertices.size() - 1;
    }

    m_index.push_back(m_vertex_to_index[a]);
}

void ObjParser::interpret_v_line(std::string& line)
{
    float x = 0.0, y = 0.0, z = 0.0, w = 0.0;
    sscanf(line.c_str(), "v %f %f %f %f", &x, &y, &z, &w);
    m_tmp_vertex_storage.emplace_back(x, y, z, w);
}

void ObjParser::interpret_vt_line(std::string& line)
{
    float u = 0.0, v = 0.0;
    sscanf(line.c_str(), "vt %f %f", &u, &v);
    v = 1.0 - v; // To OpenGL and Metal coords.
    m_tmp_texture_storage.emplace_back(u, v);
}

void ObjParser::interpret_f_line(std::string& line)
{
    std::vector<int3> data;

    int i = 2;
    while (i < line.size()) {
        int a, b, c;
        sscanf(&line.c_str()[i], "%d/%d/%d", &a, &b, &c);
        data.emplace_back(a, b, c);
        while (i < line.size() && line[i] != ' ') {
            i++;
        }
        i++;
    }

    if (data.size() != 3) {
        std::cout << "Could not load " << m_filename << ": face is not triangulated!";
        std::abort();
    }

    paste_face_to_va(data[0], data[1], data[2]);
}