#pragma once

#include <Runtime/MacOS/Window.h>
#include <mtlpp/mtlpp.hpp>
#include <string>

namespace Metal {

class Display {
public:
    Display(size_t width, size_t height, void (*render)(const Runtime::MacOS::Window&));
    ~Display();

    void swap_buffers();
    void clear(float r, float g, float b, float a);

    void run() { Runtime::MacOS::Window::Run(); }
    MTL::Device device() { return m_device; }

public:
    bool closed() const { return m_closed; }

private:
    bool m_closed {};
    Runtime::MacOS::Window* m_window;
    MTL::Device m_device;
};

}