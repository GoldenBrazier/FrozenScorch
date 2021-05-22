#include <Application/Application.h>
#include <Application/Events/KeyboardEvent.h>
#include <GraphicsAPI/Generic/Context.h>
#include <GraphicsAPI/Metal/Display.h>
#include <iostream>
#include <mtlpp/mtlpp.hpp>

namespace Metal {

Display::Display(size_t width, size_t height, const std::string& name)
{
    Ctx.set_metal_context(Metal::Context::construct(MTL::Device::CreateSystemDefaultDevice()));
    Ctx.metal_context()->set_window(new Support::MacOS::Window(Ctx.metal_context()->device(), width, height));

    Ctx.metal_context()->window().set_draw_callback(draw_cycle_callback);
    Ctx.metal_context()->window().set_key_down_callback(key_callback);
    Ctx.metal_context()->window().set_mouse_move_callback(mouse_move_callback);
    Ctx.metal_context()->window().set_mouse_down_callback(mouse_down_callback);
}

void Display::draw_cycle_callback()
{
    Ctx.application()->draw_cycle();
}

void Display::key_callback(int a, int b)
{
    auto application = Ctx.application();
    // TODO: construct an event and call application->on_event();
}

void Display::mouse_move_callback(float a, float b)
{
    auto application = Ctx.application();
    // TODO: construct an event and call application->on_event();
}

void Display::mouse_down_callback(int a, int b)
{
    auto application = Ctx.application();
    // TODO: construct an event and call application->on_event();
}

}