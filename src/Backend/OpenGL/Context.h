#pragma once

#include <SDL2/SDL.h>
#include <Utils.h>

namespace GL {

class Context {
    CONSTRUCTIBLE(Context);

public:
    explicit Context(SDL_GLContext context)
        : m_sdl_glcontext(context)
    {
    }

    ~Context() = default;

    SDL_GLContext sdl_glcontext() const { return m_sdl_glcontext; }

private:
    SDL_GLContext m_sdl_glcontext;
};

}