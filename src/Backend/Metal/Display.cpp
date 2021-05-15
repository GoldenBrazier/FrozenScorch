#include <Backend/Metal/Display.h>
#include <iostream>
#include <mtlpp/mtlpp.hpp>

namespace Metal {

Display::Display(size_t width, size_t height, void (*render)(const Runtime::MacOS::Window&))
{
    m_device = MTL::Device::CreateSystemDefaultDevice();
    m_window = new Runtime::MacOS::Window(m_device, render, 800, 600);
}

Display::~Display()
{
}

void Display::swap_buffers()
{
}

void Display::clear(float r, float g, float b, float a)
{
}

}