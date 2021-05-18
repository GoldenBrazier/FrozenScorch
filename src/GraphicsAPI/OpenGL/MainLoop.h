#pragma once
#include <GraphicsAPI/Generic/MainLoop.h>
#include <Runtime/Utils/DrawLoop.h>
#include <functional>

namespace GL {

class MainLoop : public Generic::MainLoop {
public:
    explicit MainLoop(std::function<void(void)> callback)
        : m_callback(callback)
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