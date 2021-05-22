#include "Application.h"
#include <GraphicsAPI/Generic/Constructors.h>
#include <GraphicsAPI/Generic/Context.h>
#include <GraphicsAPI/Generic/Display.h>
#include <GraphicsAPI/Generic/Context.h>

Application::Application()
{
    m_display = Constructors::Display::construct(800, 600, "OpenRenderer");
    Ctx.set_application(this);
}

void Application::run()
{
    if (Ctx.graphics_api_type() == Generic::GraphicsAPIType::Metal) {
        Support::MacOS::Window::Run();
    } else {
        while (m_running) {
            draw_cycle();
            m_display->swap_buffers();
        }
    }
}