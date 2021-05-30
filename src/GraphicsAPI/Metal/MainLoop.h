#pragma once
#include <GraphicsAPI/Generic/Context.h>
#include <GraphicsAPI/Generic/MainLoop.h>
#include <functional>

namespace Metal {

class MainLoop : public Generic::MainLoop {
public:
    explicit MainLoop(void (*draw_callback)(), void (*key_down_callback)(int, int), void (*mouse_move_callback)(int, int), void (*mouse_down_callback)(int, int))
        : m_callback(draw_callback)
    {
        Ctx.metal_context()->window().set_draw_callback(draw_callback);
        Ctx.metal_context()->window().set_key_down_callback(key_down_callback);
        Ctx.metal_context()->window().set_mouse_move_callback(mouse_move_callback);
        Ctx.metal_context()->window().set_mouse_down_callback(mouse_down_callback);
    }

    inline void run() override
    {
        Support::MacOS::Window::Run();
    }

private:
    std::function<void(void)> m_callback;
};

}