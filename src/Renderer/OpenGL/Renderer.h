#pragma once

#include <Renderer/Renderer.h>

namespace Generic {
class VertexArray;
}

namespace GL {

class Renderer : public Generic::Renderer {
    friend class Generic::VertexArray;

public:
    // void begin() override;
    // void end() override;
    void clear() override;
    void set_clear_color(float r, float g, float b, float a) override;
    void draw_indexed(const std::shared_ptr<Generic::VertexArray>& va) override;
};

}