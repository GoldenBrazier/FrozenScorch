#pragma once
#include <GL/glew.h>
#include <GraphicsAPI/Generic/Texture.h>
#include <Runtime/Image/Image.h>
#include <iostream>
#include <string>

namespace GL {

class Texture : public Generic::Texture {
public:
    Texture(const Runtime::RawImage& texture_image, Generic::Texture::Types)
        : m_texture_image(texture_image)
        , m_texture_target(GL_TEXTURE_2D)
    {
        auto gl_format = gl_color_format(texture_image.type());
        glGenTextures(1, &m_texture_object);
        glBindTexture(m_texture_target, m_texture_object);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(m_texture_target, 0, gl_format, texture_image.width(), texture_image.height(), 0, gl_format, GL_UNSIGNED_BYTE, texture_image.data<void*>());
        glTexParameterf(m_texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(m_texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void bind(int texture_unit) override
    {
        GLenum gl_tex_unit = GL_TEXTURE0 + texture_unit;
        glActiveTexture(gl_tex_unit);
        glBindTexture(m_texture_target, m_texture_object);
    }

private:
    GLenum gl_color_format(Runtime::ImageType type)
    {
        static const GLenum gl_mapping[] = {
            [Runtime::ImageType::RGB] = GL_RGB,
            [Runtime::ImageType::RGBA] = GL_RGBA,
        };
        return gl_mapping[type];
    }

    GLuint m_texture_object;
    GLenum m_texture_target;
    Runtime::RawImage m_texture_image;
};

}