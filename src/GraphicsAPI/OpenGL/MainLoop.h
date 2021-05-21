#pragma once
#include <GraphicsAPI/Generic/MainLoop.h>
#include <Runtime/Utils/DrawLoop.h>
#include <functional>

namespace GL {

class MainLoop : public Generic::MainLoop {
public:
    explicit MainLoop(void (*draw_callback)(), void (*key_down_callback)(int, int), void (*mouse_move_callback)(float, float), void (*mouse_down_callback)(int, int))
        : m_callback(draw_callback)
    {
    }

    inline void run() override
    {
        Runtime::DrawLoop<Runtime::Debug::Off>(60, m_callback);
    }

private:
    std::function<void(void)> m_callback;
};

}