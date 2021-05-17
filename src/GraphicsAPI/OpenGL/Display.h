#pragma once

#include <GraphicsAPI/Generic/Display.h>
#include <SDL2/SDL.h>
#include <string>

namespace GL {

class Display : public Generic::Display {
public:
    Display(int width, int height, const std::string& name);
    ~Display();

    void swap_buffers() override;
    bool closed() const override { return m_closed; }

private:
    bool m_closed {};
    SDL_Window* m_window;
    SDL_GLContext m_gl_context;
};

}