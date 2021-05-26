#pragma once

#include <Runtime/Image/Image.h>
#include <lodepng/lodepng.h>

namespace Runtime {

class PNGLoader {
public:
    static RawImage load_rgb(const std::string& filepath)
    {
        auto res = RawImage();
        uint8_t* data;
        res.m_type = ImageType::RGB;
        lodepng_decode24_file(&data, reinterpret_cast<unsigned*>(&res.m_width), reinterpret_cast<unsigned*>(&res.m_height), filepath.c_str());
        res.set_data(data);
        return res;
    }

    static RawImage load_rgba(const std::string& filepath)
    {
        auto res = RawImage();
        uint8_t* data;
        res.m_type = ImageType::RGBA;
        lodepng_decode32_file(&data, reinterpret_cast<unsigned*>(&res.m_width), reinterpret_cast<unsigned*>(&res.m_height), filepath.c_str());
        res.set_data(data);
        return res;
    }
};

};