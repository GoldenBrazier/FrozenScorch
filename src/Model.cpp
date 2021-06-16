#include "Model.h"
#include <Config.h>
#include <filesystem>
#include <Runtime/PNGLoader/PNGLoader.h>
#include <GraphicsAPI/Generic/Constructors.h>

Model::Model(const std::string& name)
{
    auto texture_path = (std::filesystem::path(Config::ModelsFolder) / name / name).string() + ".png";
    auto obj_path = (std::filesystem::path(Config::ModelsFolder) / name / name).string() + ".obj";

    m_texture = Constructors::Texture::construct(Runtime::PNGLoader::load_rgba(texture_path), Generic::Texture::Types::TEXTURE_2D);
    m_mesh = Mesh(obj_path);
}

void Model::draw() const
{
    m_texture->bind(0);
    m_mesh.draw();
}

class BasicShader {
    static constexpr uint32_t g_scale_var = 1;
};

