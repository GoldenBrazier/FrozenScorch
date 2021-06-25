#include "Renderer.h"
#include <Config.h>
#include <GL/glew.h>
#include <GraphicsAPI/OpenGL/VertexArray.h>

namespace GL {

void Renderer::set_clear_color(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw_indexed(const std::shared_ptr<Generic::VertexArray>& va)
{
    auto va_gl = std::static_pointer_cast<GL::VertexArray>(va);
    va_gl->bind();

    glDrawElements(GL_TRIANGLES, va_gl->index_buffer()->count(), GL_UNSIGNED_INT, nullptr);
}

Generic::FramebufferIndex Renderer::create_framebuffer()
{
    GLuint color_renderbuffer;
    glGenRenderbuffers(1, &color_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, (GLuint)color_renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // Build the texture that will serve as the depth attachment for the framebuffer.
    GLuint depth_renderbuffer;
    glGenRenderbuffers(1, &depth_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, (GLuint)depth_renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, (GLuint)framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, color_renderbuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_renderbuffer);
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Error GL_FRAMEBUFFER_COMPLETE" << std::endl;
        std::abort();
    }

    ++m_next_framebuffer;
    m_framebuffers_mapping[m_next_framebuffer] = framebuffer;
    return m_next_framebuffer;
}

void Renderer::read_framebuffer(int x, int y, size_t width, size_t height, void* buffer)
{
    glReadPixels(x, Config::SCREEN_HEIGHT - y, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
}

}