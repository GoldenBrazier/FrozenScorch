#pragma once

#include <GL/glew.h>
#include <GraphicsAPI/Generic/VertexArray.h>
#include <Math/Vector3f.h>
#include <array>
#include <memory>
#include <vector>
#include <string>

class Mesh {
public:
    Mesh() = default;
    explicit Mesh(const std::string& obj_path, int position = 0, int tex_coords = 1, int normal = 2);

public:
    void draw() const;

private:
    std::shared_ptr<Generic::VertexArray> m_vertex_array {};
};