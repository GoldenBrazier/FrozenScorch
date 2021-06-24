#pragma once

#include <Application/Application.h>
#include <Config.h>
#include <ECS/ECS.h>
#include <Math/Matrix4f.h>
#include <Math/Numbers.h>
#include <Model.h>
#include <Renderer/Renderer.h>
#include <memory>
#include <utility>
#include <vector>

class RenderSystem : public System<Config::ComponentCount, Config::SystemCount> {
public:
    RenderSystem(ECS<Config::ComponentCount, Config::SystemCount>* ecs, std::shared_ptr<Generic::Renderer> renderer, EntityID camera_entity_id)
        : System<Config::ComponentCount, Config::SystemCount>(ecs)
        , m_renderer(std::move(renderer))
        , m_camera_entity_id(camera_entity_id)
        , m_camera({ 0, 0, 0 }, { 0, 1, 0 })
    {
        set_required_components<TransformComponent, ModelComponent, ShaderComponent>();
    }

    inline void update_camera()
    {
        auto& camera_component = ecs().get_component<CameraComponent>(m_camera_entity_id);
        m_camera.m_position = camera_component.position;
        m_camera.m_up = camera_component.up;
        m_camera.m_yaw = camera_component.yaw;
        m_camera.m_pitch = camera_component.pitch;
        m_camera.m_target = camera_component.target;
        m_camera.recalculate_view_matrix();
    }

    [[gnu::flatten]] void update() override
    {
        update_camera();
        m_renderer->set_clear_color(0, 0.15f, 0.3f, 1.0f);
        m_renderer->begin_scene(m_camera);
        m_renderer->clear();

        for (auto entity_id : m_managed_entities) {
            auto& model = ecs().get_component<ModelComponent>(entity_id).model;
            auto& shader = ecs().get_component<ShaderComponent>(entity_id).shader;
            auto& transform = ecs().get_component<TransformComponent>(entity_id).transform();
            m_renderer->draw_model(model, shader, transform);
        }

        m_renderer->end_scene();
    }

private:
    std::shared_ptr<Generic::Renderer> m_renderer;
    EntityID m_camera_entity_id;
    Camera m_camera;
};