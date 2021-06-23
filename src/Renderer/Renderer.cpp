#include "Renderer.h"
#include <Math/Matrix4f.h>
#include <Model.h>
#include <Application/Camera.h>

namespace Generic {

void Renderer::begin_scene(const Camera& camera)
{
    m_camera = &camera;
    begin();
}

void Renderer::end_scene()
{
    m_camera = nullptr;
    end();
}

void Renderer::draw_model(const Model& model, const std::shared_ptr<Generic::Shader>& shader, const Math::Matrix4f& transform)
{
    shader->bind();

    shader->set_uniform("g_sampler", (int)0);
    shader->set_uniform("g_transform", transform);

    shader->set_uniform("g_perspective", Math::Matrix4f::Perspective(800, 600, 0.01f, 1000.0f, 90));
    shader->set_uniform("g_viewMatrix", m_camera->view_matrix());
    shader->set_uniform("g_camera_position", m_camera->position());

    shader->set_uniform("g_ambient_brightness", 0.3f);
    shader->set_uniform("g_light_color", Math::Vector3f(1, 1, 1));

    shader->set_uniform("g_light_position", 0, m_camera->position());
    shader->set_uniform("g_light_color", 0, { 0, 0, 1 });
    shader->set_uniform("g_light_attenuation", 0, { 1, 0.09, 0.032 });

    shader->set_uniform("g_light_position", 1, { 0, 7, 0 });
    shader->set_uniform("g_light_color", 1, { 1, 0, 0 });
    shader->set_uniform("g_light_attenuation", 1, { 1, 0, 0 });

    shader->set_uniform("g_light_position", 2, { 7, 0, 0 });
    shader->set_uniform("g_light_color", 2, { 0, 1, 0 });
    shader->set_uniform("g_light_attenuation", 2, { 1, 0, 0 });

    model.draw();
}

}