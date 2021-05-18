#pragma once
#include <GraphicsAPI/Metal/Context.h>
#include <GraphicsAPI/OpenGL/Context.h>
#include <memory>

namespace Generic {

class Context {
public:
    Context() = default;
    ~Context() = default;

    std::shared_ptr<GL::Context> opengl_context() { return m_opengl_context; }
    inline void set_opengl_context(const std::shared_ptr<GL::Context>& context) { m_opengl_context = context; }

    std::shared_ptr<Metal::Context> metal_context() { return m_metal_context; }
    inline void set_metal_context(const std::shared_ptr<Metal::Context>& context) { m_metal_context = context; }

private:
    std::shared_ptr<GL::Context> m_opengl_context { nullptr };
    std::shared_ptr<Metal::Context> m_metal_context { nullptr };
};

}

extern Generic::Context Ctx;