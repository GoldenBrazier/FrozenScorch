#pragma once

#include <cstddef>
#include <memory>
#include <type_traits>

namespace Runtime {

enum ImageType {
    RGB = 0,
    RGBA,
};

class RawImage final {
    friend class PNGLoader;

public:
    RawImage() = default;
    ~RawImage() = default;

    template <typename T = char*, typename = std::enable_if_t<std::is_pointer<T>::value>>
    inline T data() const { return reinterpret_cast<T>(m_raw_data.get()); }
    inline void set_data(void* data) { m_raw_data = std::shared_ptr<char>((char*)data); }

    inline bool valid() const { return m_width != 0 && m_height != 0 && m_raw_data; }

    inline size_t width() const { return m_width; }
    inline size_t height() const { return m_height; }
    inline ImageType type() const { return m_type; }
    inline void set_type(ImageType type) { m_type = type; }

private:
    std::shared_ptr<char> m_raw_data { nullptr };
    size_t m_width { 0 };
    size_t m_height { 0 };
    ImageType m_type;
};

};