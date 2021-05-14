#pragma once

#include <Runtime/Image/Image.h>
#include <lodepng/lodepng.h>

namespace Runtime {

class PNGLoader {
public:
    template <ImageType Type>
    constexpr static RawImage load(const std::string& filepath)
    {
        auto res = RawImage();
        res.m_type = Type;
        if constexpr (Type == ImageType::RGB) {
            lodepng_decode24_file(reinterpret_cast<uint8_t**>(&res.m_raw_data), reinterpret_cast<unsigned*>(&res.m_width), reinterpret_cast<unsigned*>(&res.m_height), filepath.c_str());
        } else if constexpr (Type == ImageType::RGBA) {
            lodepng_decode32_file(reinterpret_cast<uint8_t**>(&res.m_raw_data), reinterpret_cast<unsigned*>(&res.m_width), reinterpret_cast<unsigned*>(&res.m_height), filepath.c_str());
        }
        return res;
    }
};

};