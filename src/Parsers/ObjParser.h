#pragma once
#include <GraphicsAPI/Generic/Vertex.h>
#include <GraphicsAPI/Generic/VertexArray.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

// FIXME: std::tuple doesn't have hash, so we can't use std::unordered_map,
// which potentially could be faster than std::map.
using int3 = std::tuple<int, int, int>;
using float2 = std::tuple<float, float>;
using float3 = std::tuple<float, float, float>;
using float4 = std::tuple<float, float, float, float>;

class ObjParser final {
public:
    explicit ObjParser(const std::string& filename)
        : m_filename(filename)
    {
    }

    explicit ObjParser(std::string&& filename)
        : m_filename(std::move(filename))
    {
    }

    ~ObjParser() = default;

    int parse()
    {
        auto file = std::ifstream(m_filename);

        std::string line;

        while (getline(file, line)) {
            interpret_line(line);
        }

        // TODO: Return error codes.
        return 0;
    }

    const std::vector<Generic::Vertex>& vertexes() const { return m_vertices; }
    std::vector<Generic::Vertex>& vertexes() { return m_vertices; }

    const std::vector<uint32_t>& indeces() const { return m_index; }
    std::vector<uint32_t>& indeces() { return m_index; }

private:
    inline bool starts_with(const std::string& s, const std::string& w) { return s.rfind(w, 0) == 0; }

    inline void interpret_line(std::string& line)
    {
        if (starts_with(line, "v ")) {
            interpret_v_line(line);
        } else if (starts_with(line, "vt ")) {
            interpret_vt_line(line);
        } else if (starts_with(line, "f ")) {
            interpret_f_line(line);
        } else if (starts_with(line, "vn ")) {
            interpret_vn_line(line);
        }
    }

    void interpret_v_line(std::string& line);
    void interpret_vt_line(std::string& line);
    void interpret_f_line(std::string& line);
    void interpret_vn_line(std::string& line);

    void paste_vertex_to_va(int3 a);
    inline void paste_face_to_va(int3 a, int3 b, int3 c)
    {
        paste_vertex_to_va(a);
        paste_vertex_to_va(b);
        paste_vertex_to_va(c);
    }

    std::string m_filename;
    std::vector<float4> m_tmp_vertex_storage;
    std::vector<float2> m_tmp_texture_storage;
    std::vector<float3> m_tmp_normals_storage;
    std::vector<Generic::Vertex> m_vertices;
    std::vector<uint32_t> m_index;
    std::map<int3, int> m_vertex_to_index;
};