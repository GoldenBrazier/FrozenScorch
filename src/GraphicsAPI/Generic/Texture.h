#pragma once
#include <cstddef>
#include <string>

namespace Generic {

class Texture {
public:
    enum Types {
        TEXTURE_1D,
        TEXTURE_2D,
        TEXTURE_3D
    };

    virtual ~Texture() = default;
    virtual void bind(int texture_unit) {};
    virtual const std::string& path() const = 0;
};

}