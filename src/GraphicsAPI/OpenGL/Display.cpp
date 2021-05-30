#include <Application/Application.h>
#include <Application/Events/KeyboardEvent.h>
#include <Application/Events/MouseEvent.h>
#include <Application/Events/WindowEvent.h>
#include <GL/glew.h>
#include <GraphicsAPI/Generic/Context.h>
#include <GraphicsAPI/OpenGL/Display.h>
#include <cassert>
#include <iostream>

namespace GL {

Display::Display(size_t width, size_t height, const std::string& name)
{
    // GLEW obtains information on the supported extensions from the graphics driver.
    // Experimental or pre-release drivers, however, might not report every available
    // extension through the standard mechanism, in which case GLEW will report it is
    // unsupported. To circumvent this situation, the glewExperimental can be turned
    // on before calling glewInit().
    glewExperimental = GL_TRUE;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    Ctx.set_opengl_context(GL::Context::construct(SDL_GL_CreateContext(m_window)));

    auto status = glewInit();
    if (status != GLEW_OK) {
        std::cerr << "glew initialization failed" << std::endl;
        std::abort();
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

Display::~Display()
{
    SDL_GL_DeleteContext(Ctx.opengl_context()->sdl_glcontext());
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::swap_buffers()
{
    SDL_GL_SwapWindow(m_window);
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        switch (event.type) {
        case SDL_QUIT: {
            Ctx.application()->on_event(WindowCloseEvent());
            break;
        }
        case SDL_KEYUP: {
            Ctx.application()->on_event(KeyboardReleasedEvent(OpenRenderer::keycode_from_sdl(event.key.keysym.scancode)));
            break;
        }
        case SDL_KEYDOWN: {
            Ctx.application()->on_event(KeyboardPressedEvent(OpenRenderer::keycode_from_sdl(event.key.keysym.scancode)));
            break;
        }

        case SDL_MOUSEMOTION: {
            Ctx.application()->on_event(MouseMoveEvent(event.motion.xrel, event.motion.yrel));
            break;
        }

        default:
            break;
        }
    }
}

}