#pragma once

#include <Config.h>
#include <GraphicsAPI/Generic/Shader.h>
#include <GraphicsAPI/Generic/VertexArray.h>
#include <Model.h>
#include <functional>
#include <memory>
#include <string>

class Camera;

namespace Generic {

using FramebufferIndex = size_t;

struct SceneData {
    Math::Vector3f camera_position {};
    Math::Matrix4f camera_view_matrix {};
    float camera_field_of_view {};
    float camera_near_clipping {};
    float camera_far_clipping {};
};

class Renderer {
public:
    // Scene
    void begin_scene(const SceneData& scene_data);
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
    inline void draw_model(const Model& model, const std::shared_ptr<Generic::Shader>& shader, const Math::Matrix4f& transform, std::function<void(std::shared_ptr<Generic::Shader>)> uniform_setter)
    {
        shader->bind();

        set_scene_data(shader);

        shader->set_uniform("g_transform", transform);

        uniform_setter(shader);
        model.draw();
    }

protected:
    // GraphicsAPI specific function.
    virtual void begin() {};
    virtual void end() {};

private:
    inline void set_scene_data(const std::shared_ptr<Generic::Shader>& shader)
    {
        shader->set_uniform("g_perspective",
            Math::Matrix4f::Perspective(
                Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT,
                m_scene_data.camera_near_clipping, m_scene_data.camera_far_clipping,
                m_scene_data.camera_field_of_view));

        shader->set_uniform("g_viewMatrix", m_scene_data.camera_view_matrix);
        shader->set_uniform("g_camera_position", m_scene_data.camera_position);

        shader->set_uniform("g_light_position", 0, m_scene_data.camera_position);
    }

private:
    SceneData m_scene_data {};
};

}