#pragma once

#include <Renderer/Renderer.h>
#include <mtlpp/mtlpp.hpp>

namespace Generic {
class VertexArray;
}

namespace Metal {

class Renderer : public Generic::Renderer {
    friend class Generic::VertexArray;

public:
    void begin() override;
    void end() override;

    void set_clear_color(float r, float g, float b, float a) override;
    // void clear() override;

    void draw_indexed(const std::shared_ptr<Generic::VertexArray>& va) override;

private:
    inline mtlpp::RenderCommandEncoder& command_encoder() { return m_command_encoder; }

private:
    float m_r, m_g, m_b, m_a;
    MTL::CommandBuffer m_command_buffer;
    MTL::RenderCommandEncoder m_command_encoder;

    MTL::RenderPassDescriptor m_renderpass_descriptor;
};

}