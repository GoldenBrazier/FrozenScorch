#pragma once
#include <GraphicsAPI/OpenGL/Context.h>
#include <memory>

namespace Generic {

class Context {
public:
    Context() = default;
    ~Context() = default;

    std::shared_ptr<GL::Context> opengl_context() { return m_opengl_context; }
    inline void set_opengl_context(const std::shared_ptr<GL::Context>& context) { m_opengl_context = context; }

private:
    std::shared_ptr<GL::Context> m_opengl_context { nullptr };
};

}

extern Generic::Context Ctx;