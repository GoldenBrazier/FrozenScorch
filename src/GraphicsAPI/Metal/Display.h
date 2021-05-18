#pragma once
#include <GraphicsAPI/Generic/Display.h>
#include <mtlpp/mtlpp.hpp>
#include <string>

namespace Metal {

class Display : public Generic::Display {
public:
    Display(size_t width, size_t height, const std::string& name);
    ~Display();

    void swap_buffers() override {};
    bool closed() const override { return false; }
};

}