#pragma once

#include <GraphicsAPI/Generic/Texture.h>
#include <Mesh.h>
#include <string>

class Model {
public:
    Model() = default;
    explicit Model(const std::string& name);

    void draw() const;
    const Mesh& mesh() const { return m_mesh; }

private:
    // there might be multiple textures for a model
    std::shared_ptr<Generic::Texture> m_texture {};
    // TODO: diffuse, metal, normal maps should be placed here
    // there might be multiple meshes for a model
    Mesh m_mesh {};
};