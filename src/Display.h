#pragma once

#include <SDL2/SDL.h>
#include <string>

class Display {
public:
    Display(int widht, int height, const std::string& name);
    ~Display();

    void swap_buffers();
    void clear(float r, float g, float b, float a);

public:
    bool closed() const { return m_closed; }

private:
    bool m_closed {};
    SDL_Window* m_window;
    SDL_GLContext m_gl_context;
};