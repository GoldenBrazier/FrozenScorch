#include "Renderer.h"
#include <Application/Camera.h>
#include <Math/Matrix4f.h>
#include <Model.h>

namespace Generic {

void Renderer::begin_scene(const SceneData& scene_data)
{
    m_scene_data = scene_data;
    begin();
}

void Renderer::end_scene()
{
    end();
}

void Renderer::draw_model(const Model& model, const std::shared_ptr<Generic::Shader>& shader, const Math::Matrix4f& transform, bool focused)
{
    shader->bind();

    set_scene_data(shader);

    shader->set_uniform("g_debug_focused", (float)focused);

    shader->set_uniform("g_sampler", (int)0);
    shader->set_uniform("g_transform", transform);

    shader->set_uniform("g_ambient_brightness", 0.3f);
    shader->set_uniform("g_light_color", Math::Vector3f(1, 1, 1));

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