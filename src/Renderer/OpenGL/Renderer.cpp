#include "Renderer.h"
#include <GL/glew.h>
#include <GraphicsAPI/OpenGL/VertexArray.h>

namespace GL {

void Renderer::set_clear_color(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw_indexed(const std::shared_ptr<Generic::VertexArray>& va)
{
    auto va_gl = std::static_pointer_cast<GL::VertexArray>(va);
    va_gl->bind();

    glDrawElements(GL_TRIANGLES, va_gl->index_buffer()->count(), GL_UNSIGNED_INT, nullptr);
}

}