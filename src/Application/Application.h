#pragma once

#include "Events/Event.h"
#include <GraphicsAPI/Generic/Display.h>
#include <Scene/Scene.h>
#include <memory>

class Application {
public:
    Application();
    virtual ~Application() = default;

public:
    void run();
    inline void shutdown() { m_running = false; }
    void on_event_base(const Event& event);

    virtual void draw_cycle() = 0;
    virtual void on_event(const Event& event) = 0;

protected:
    Scene& scene() { return m_scene; }
    std::shared_ptr<Generic::Display>& display() { return m_display; }

private:
    static void compile_shaders();

protected:
    bool m_running { true };

private:
    std::shared_ptr<Generic::Display> m_display;
    Scene m_scene {};
};