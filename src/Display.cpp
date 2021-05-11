#include "Display.h"
#include <GL/glew.h>
#include <iostream>

Display::Display(int widht, int height, const std::string& name)
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

    m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, widht, height, SDL_WINDOW_OPENGL);
    m_gl_context = SDL_GL_CreateContext(m_window);

    auto status = glewInit();
    if (status != GLEW_OK) {
        std::cerr << "glew initialization failed" << std::endl;
        exit(1);
    }
}

Display::~Display()
{
    SDL_GL_DeleteContext(m_gl_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::swap_buffers()
{
    SDL_GL_SwapWindow(m_window);
    SDL_Event windowEvent;
    while (SDL_PollEvent(&windowEvent)) {
        if (windowEvent.type == SDL_QUIT) {
            m_closed = true;
        }
    }
}

void Display::clear(float r, float g, float b, float a)
{
    glClearColor(0, 0.15f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}