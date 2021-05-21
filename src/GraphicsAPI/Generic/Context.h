#pragma once
#include <GraphicsAPI/Metal/Context.h>
#include <GraphicsAPI/OpenGL/Context.h>
#include <memory>

namespace Generic {

enum class GraphicsAPIType {
    OpenGL,
    Metal,
};

class Context {
public:
    Context() = default;
    ~Context() = default;

    inline std::shared_ptr<GL::Context> opengl_context() { return m_opengl_context; }
    inline void set_opengl_context(const std::shared_ptr<GL::Context>& context) { m_opengl_context = context; }

    inline std::shared_ptr<Metal::Context> metal_context() { return m_metal_context; }
    inline void set_metal_context(const std::shared_ptr<Metal::Context>& context) { m_metal_context = context; }

    inline void set_grahics_api_type(GraphicsAPIType api) { m_graphics_api_type = api; }
    inline GraphicsAPIType graphics_api_type() const { return m_graphics_api_type; }

private:
    GraphicsAPIType m_graphics_api_type;
    std::shared_ptr<GL::Context> m_opengl_context { nullptr };
    std::shared_ptr<Metal::Context> m_metal_context { nullptr };
};

}

extern Generic::Context Ctx;