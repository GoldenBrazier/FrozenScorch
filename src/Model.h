#pragma once

#include <GraphicsAPI/Generic/Texture.h>
#include <Mesh.h>
#include <string>

class Model {
public:
    Model() = default;
    explicit Model(const std::string& name);

    void draw() const;

    Mesh& mesh() { return m_mesh; }
    const Mesh& mesh() const { return m_mesh; }
    void set_mesh(const Mesh& mesh) { m_mesh = mesh; }
    void set_mesh(Mesh&& mesh) { m_mesh = std::move(mesh); }

    std::shared_ptr<Generic::Texture> texture() const { return m_texture; }
    void set_texture(std::shared_ptr<Generic::Texture> texture) { m_texture = texture; }

private:
    // there might be multiple textures for a model
    std::shared_ptr<Generic::Texture> m_texture {};
    // TODO: diffuse, metal, normal maps should be placed here
    // there might be multiple meshes for a model
    Mesh m_mesh {};
};