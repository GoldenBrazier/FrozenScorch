#pragma once

#include <GraphicsAPI/Generic/Shader.h>
#include <GraphicsAPI/Generic/VertexArray.h>
#include <Model.h>
#include <functional>
#include <memory>
#include <string>

class Camera;

namespace Generic {

using FramebufferIndex = size_t;

class Renderer {
public:
    // Scene
    void begin_scene(const Camera& camera);
    void end_scene();

    // Draw
    virtual void set_clear_color(float r, float g, float b, float a) = 0;
    virtual void clear() {};
    virtual FramebufferIndex create_framebuffer() = 0;
    virtual void bind_framebuffer(FramebufferIndex) = 0;
    virtual void bind_standard_framebuffer() = 0;
    virtual void read_framebuffer(int x, int y, size_t width, size_t height, void* buffer) = 0;

    virtual void draw_indexed(const std::shared_ptr<Generic::VertexArray>& va) = 0;

    void draw_model(const Model& model, const std::shared_ptr<Generic::Shader>& shader, const Math::Matrix4f& transform, bool focused = false);
    void draw_model(const Model& model, const std::shared_ptr<Generic::Shader>& shader, const Math::Matrix4f& transform, std::function<void(std::shared_ptr<Generic::Shader>)> uniform_setter);

protected:
    // GraphicsAPI specific function.
    virtual void begin() {};
    virtual void end() {};

private:
    const Camera* m_camera {};
};

}