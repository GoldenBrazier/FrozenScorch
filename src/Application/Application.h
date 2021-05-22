#pragma once

#include "Events/Event.h"
#include <GraphicsAPI/Generic/Display.h>
#include <memory>

class Application {
public:
    Application();

public:
    void run();
    inline void shutdown() { m_running = false; }

public:
    virtual void draw_cycle() = 0;
    virtual void on_event(const Event& event) = 0;

protected:
    std::shared_ptr<Generic::Display> m_display;
    bool m_running { true };
};