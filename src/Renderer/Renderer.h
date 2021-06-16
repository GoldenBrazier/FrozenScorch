#pragma once

#include <GraphicsAPI/Generic/VertexArray.h>
#include <Model.h>
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

    // TODO: pass here a transformation matrix and a camera so we don't deal with this in main.cpp
    void draw_model(const Model& model);
};

}