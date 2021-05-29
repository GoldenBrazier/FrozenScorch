#pragma once
#include <GraphicsAPI/Generic/Display.h>
#include <SDL.h>
#include <string>

namespace GL {

class Display : public Generic::Display {
public:
    Display(size_t width, size_t height, const std::string& name);
    ~Display();

    void swap_buffers() override;
    bool closed() const override { return m_closed; }

private:
    bool m_closed {};
    SDL_Window* m_window;
};

}