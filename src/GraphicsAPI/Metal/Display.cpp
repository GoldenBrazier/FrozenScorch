#include <GraphicsAPI/Generic/Context.h>
#include <GraphicsAPI/Metal/Display.h>
#include <iostream>
#include <mtlpp/mtlpp.hpp>

namespace Metal {

Display::Display(size_t width, size_t height, const std::string& name)
{
    Ctx.set_metal_context(Metal::Context::construct(MTL::Device::CreateSystemDefaultDevice()));
}

Display::~Display()
{
}

}