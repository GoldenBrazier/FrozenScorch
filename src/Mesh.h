#pragma once

#include <GL/glew.h>
#include <GraphicsAPI/Generic/VertexArray.h>
#include <Math/Vector3f.h>
#include <array>
#include <memory>
#include <string>
#include <vector>

class Mesh {
public:
    Mesh() = default;
    explicit Mesh(const std::string& obj_path, int position = 0, int tex_coords = 1, int normal = 2);

    void draw() const;
    std::shared_ptr<Generic::VertexArray> vertex_array() const { return m_vertex_array; }

    const std::string& object_path() const { return m_obj_path; }

private:
    std::string m_obj_path {};
    std::shared_ptr<Generic::VertexArray> m_vertex_array {};
};