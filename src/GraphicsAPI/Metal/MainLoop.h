#pragma once
#include <GraphicsAPI/Generic/Context.h>
#include <GraphicsAPI/Generic/MainLoop.h>
#include <functional>

namespace Metal {

class MainLoop : public Generic::MainLoop {
public:
    explicit MainLoop(void (*callback)())
        : m_callback(callback)
    {
        Ctx.metal_context()->set_window(new Support::MacOS::Window(Ctx.metal_context()->device(), callback, 800, 600));
    }

    inline void run() override
    {
        Support::MacOS::Window::Run();
    }

private:
    std::function<void(void)> m_callback;
};

}