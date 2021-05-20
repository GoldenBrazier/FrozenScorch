#pragma once

#include <GraphicsAPI/Generic/VertexArray.h>
#include <memory>

namespace Generic {

class Renderer {
public:
    // Scene
    virtual void begin() {};
    virtual void end() {};

public:
    // Draw
    virtual void set_clear_color(float r, float g, float b, float a) = 0;
    virtual void clear() {};

    virtual void draw_indexed(const std::shared_ptr<Generic::VertexArray>& va) = 0;
};

}