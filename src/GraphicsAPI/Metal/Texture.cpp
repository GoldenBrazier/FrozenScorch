#include "Texture.h"
#include <GraphicsAPI/Generic/Context.h>
#include <cstddef>
#include <cstdint>
#include <new>

namespace Metal {

void Texture::add_alpha_chennel()
{
    if (m_texture_image.type() == Runtime::ImageType::RGBA) {
        return;
    }

    uint8_t* old_data = m_texture_image.data<uint8_t*>();
    uint8_t* new_data = (uint8_t*)new uint32_t[m_texture_image.height() * m_texture_image.width()];

    for (size_t i = 0; i < m_texture_image.height(); i++) {
        for (size_t j = 0; j < m_texture_image.width(); j++) {
            size_t src_index = 3 * (i * m_texture_image.width() + j);
            size_t dst_index = 4 * (i * m_texture_image.width() + j);
            new_data[dst_index + 0] = old_data[src_index + 0];
            new_data[dst_index + 1] = old_data[src_index + 1];
            new_data[dst_index + 2] = old_data[src_index + 2];
            new_data[dst_index + 3] = 255;
        }
    }
    
    m_texture_image.set_data(new_data);
    m_texture_image.set_type(Runtime::ImageType::RGBA);
}

}
