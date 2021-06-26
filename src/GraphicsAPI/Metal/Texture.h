#pragma once
#include <GraphicsAPI/Generic/Context.h>
#include <GraphicsAPI/Generic/Texture.h>
#include <Runtime/Image/Image.h>
#include <Runtime/PNGLoader/PNGLoader.h>
#include <iostream>
#include <mtlpp/mtlpp.hpp>
#include <string>

namespace Metal {

class Texture : public Generic::Texture {
public:
    Texture(const std::string& texture_path, Generic::Texture::Types)
        : m_texture_path(texture_path)
    {
        m_texture_image = Runtime::PNGLoader::load_rgba(m_texture_path);

        if (m_texture_image.type() != Runtime::ImageType::RGBA) {
            add_alpha_chennel();
        }

        auto metal_context = Ctx.metal_context();
        auto texture_desc = MTL::TextureDescriptor::Texture2DDescriptor(MTL::PixelFormat::RGBA8Unorm, m_texture_image.width(), m_texture_image.height(), false);
        m_texture = metal_context->device().NewTexture(texture_desc);

        MTL::Region fill_region(0, 0, 0, m_texture_image.width(), m_texture_image.height(), 1);
        m_texture.Replace(fill_region, 0, m_texture_image.data(), 4 * m_texture_image.width());
    }

    void bind(int texture_unit) override
    {
        auto rc_encoder = Ctx.metal_context()->render_encoder();
        rc_encoder->SetFragmentTexture(m_texture, texture_unit);
    }

    const std::string& path() const override { return m_texture_path; }

private:
    void add_alpha_chennel();

    MTL::Texture m_texture;
    Runtime::RawImage m_texture_image;
    std::string m_texture_path;
};
}