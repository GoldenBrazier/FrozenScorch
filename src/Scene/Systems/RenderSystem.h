#pragma once

#include <Application/Application.h>
#include <Config.h>
#include <ECS/ECS.h>
#include <Math/Matrix4f.h>
#include <Math/Numbers.h>
#include <Model.h>
#include <Renderer/Renderer.h>
#include <cmath>
#include <memory>
#include <utility>
#include <vector>

class RenderSystem : public System<Config::ComponentCount, Config::SystemCount> {
public:
    RenderSystem(ECS<Config::ComponentCount, Config::SystemCount>* ecs, std::shared_ptr<Generic::Renderer> renderer, EntityID camera_entity_id)
        : System<Config::ComponentCount, Config::SystemCount>(ecs)
        , m_renderer(std::move(renderer))
        , m_camera_entity_id(camera_entity_id)
    {
        set_required_components<TransformComponent, ModelComponent, ShaderComponent>();
    }

    [[gnu::flatten]] void update() override
    {
        auto& camera_transform_component = ecs().get_component<TransformComponent>(m_camera_entity_id);
        auto& camera_camera_component = ecs().get_component<CameraComponent>(m_camera_entity_id);

        m_renderer->bind_standard_framebuffer();
        m_renderer->set_clear_color(0, 0.15f, 0.3f, 1.0f);
        m_renderer->begin_scene({
            camera_transform_component.position,
            camera_transform_component.calc_view_matrix(),
            camera_camera_component.field_of_view,
            camera_camera_component.near_clipping,
            camera_camera_component.far_clipping,
        });
        m_renderer->clear();

        for (auto entity_id : m_managed_entities) {
            auto& model = ecs().get_component<ModelComponent>(entity_id).model;
            auto& shader = ecs().get_component<ShaderComponent>(entity_id).shader;
            auto& transform = ecs().get_component<TransformComponent>(entity_id);

            bool focused = false;
            if (ecs().entity_has_component<FocusableComponent>(entity_id)) {
                focused = ecs().get_component<FocusableComponent>(entity_id).focused;
            }

            auto transform_matrix = Math::Matrix4f::Translation(transform.position) * Math::Matrix4f::RotationAroundX(transform.rotation.x()) * Math::Matrix4f::RotationAroundX(transform.rotation.y()) * Math::Matrix4f::RotationAroundX(transform.rotation.z()) * Math::Matrix4f::Scaling(transform.scale);

            m_renderer->draw_model(model, shader, transform_matrix, focused);
        }

        m_renderer->end_scene();
    }

private:
    std::shared_ptr<Generic::Renderer> m_renderer;
    EntityID m_camera_entity_id;
};