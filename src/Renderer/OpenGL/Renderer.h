#pragma once

#include <Config.h>
#include <Renderer/Renderer.h>
#include <iostream>
#include <unordered_map>

namespace Generic {
class VertexArray;
}

namespace GL {

class Renderer : public Generic::Renderer {
    friend class Generic::VertexArray;

public:
    Renderer()
    {
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_sdl_buffer);
    }

    // void begin() override;
    // void end() override;
    void clear() override;
    void set_clear_color(float r, float g, float b, float a) override;
    void draw_indexed(const std::shared_ptr<Generic::VertexArray>& va) override;

    Generic::FramebufferIndex create_framebuffer() override;
    void bind_framebuffer(Generic::FramebufferIndex fbi) override { glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffers_mapping[fbi]); }
    void bind_standard_framebuffer() override { glBindFramebuffer(GL_FRAMEBUFFER, m_sdl_buffer); }

    void read_framebuffer(int x, int y, size_t width, size_t height, void* buffer) override;

private:
    GLint m_sdl_buffer;
    std::unordered_map<Generic::FramebufferIndex, GLuint> m_framebuffers_mapping;
    Generic::FramebufferIndex m_next_framebuffer { 0 };
};

}