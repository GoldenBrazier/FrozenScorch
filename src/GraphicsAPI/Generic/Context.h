#pragma once
#include <Application/Application.h>
#include <GraphicsAPI/Generic/Shader.h>
#include <GraphicsAPI/OpenGL/Context.h>
#include <memory>

#ifdef __APPLE__
#include <GraphicsAPI/Metal/Context.h>
#endif

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

#ifdef __APPLE__
public:
    inline std::shared_ptr<Metal::Context> metal_context()
    {
        return m_metal_context;
    }
    inline void set_metal_context(const std::shared_ptr<Metal::Context>& context) { m_metal_context = context; }

private:
    std::shared_ptr<Metal::Context> m_metal_context { nullptr };

public:
#endif

    inline void set_grahics_api_type(GraphicsAPIType api)
    {
        m_graphics_api_type = api;
    }
    inline GraphicsAPIType graphics_api_type() const { return m_graphics_api_type; }

    inline void set_application(Application* app) { m_application = app; }
    inline Application* application() { return m_application; }

    inline ShaderStorage& shader_storage() { return m_shader_storage; }

private:
    GraphicsAPIType m_graphics_api_type;
    std::shared_ptr<GL::Context> m_opengl_context { nullptr };
    Application* m_application { nullptr };
    ShaderStorage m_shader_storage {};
};

}

extern Generic::Context Ctx;