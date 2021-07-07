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

class MouseRayCastingSystem : public System<Config::ComponentCount, Config::SystemCount> {
public:
    MouseRayCastingSystem(ECS<Config::ComponentCount, Config::SystemCount>* iecs, std::shared_ptr<Generic::Renderer> renderer, std::shared_ptr<Generic::Shader> shader, EntityID camera_entity_id)
        : System<Config::ComponentCount, Config::SystemCount>(iecs)
        , m_renderer(std::move(renderer))
        , m_mapper2d_shader(std::move(shader))
        , m_camera_entity_id(camera_entity_id)
        , m_camera({ 0, 0, 0 }, { 0, 1, 0 })
    {
        set_required_components<PureTransformComponent, ModelComponent, ShaderComponent>();
        ecs().subscribe_for_events<MouseButtonInputEvent>([this](const BaseEvent& event) { handle_callback(event); });
        m_fb_index = m_renderer->create_framebuffer();
    }

    [[gnu::flatten]] void update() override
    {
        if (!m_mouse_was_clicked) {
            return;
        }

        update_camera();
        m_renderer->bind_framebuffer(m_fb_index);
        m_renderer->set_clear_color(1.0f, 1.0f, 1.0f, 1.0f);
        m_renderer->begin_scene(m_camera);
        m_renderer->clear();

        for (auto entity_id : m_managed_entities) {
            m_cur_draw_entity_id = entity_id;
            auto& model = ecs().get_component<ModelComponent>(entity_id).model;
            auto& transform = ecs().get_component<PureTransformComponent>(entity_id);

            auto transform_matrix = Math::Matrix4f::Translation(transform.position) *
                Math::Matrix4f::RotationAroundX(transform.rotation.x()) *
                Math::Matrix4f::RotationAroundX(transform.rotation.y()) *
                Math::Matrix4f::RotationAroundX(transform.rotation.z()) *
                Math::Matrix4f::Scaling(transform.scale);

            m_renderer->draw_model(model, m_mapper2d_shader, transform_matrix, [this](std::shared_ptr<Generic::Shader> shader) {
                shader->set_uniform("g_model_id", entity_id_to_vec3(m_cur_draw_entity_id));
            });
        }

        m_renderer->end_scene();

        uint8_t pixel[3];
        m_renderer->read_framebuffer(m_mouse_x, m_mouse_y, 1, 1, &pixel);

        EntityID target;
        if (pixel_to_entity_id(pixel, target)) {
            if (ecs().has_entity(target)) {
                ecs().post_event<MouseEntityClickEvent>(target);
            }
        }
        m_mouse_was_clicked = false;
    }

    void handle_callback(const BaseEvent& ecs_event)
    {
        if (ecs_event.id() == EventEnumerator<MouseButtonInputEvent>::ID) {
            const BaseMouseButtonEvent& mouse_event = ((const MouseButtonInputEvent&)ecs_event).event;
            if (mouse_event.type() == EventType::MouseButtonPressed) {
                if (mouse_event.button() == MouseCode::LeftButton) {
                    m_mouse_x = mouse_event.x();
                    m_mouse_y = mouse_event.y();
                    m_mouse_was_clicked = true;
                }
            }
        }
    }

private:
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

    Math::Vector3f entity_id_to_vec3(EntityID entity_id)
    {
        int r = (entity_id / (256 * 256));
        int g = (entity_id % (256 * 256)) / 256;
        int b = (entity_id % 256);
        return Math::Vector3f(float(r) / 255, float(g) / 255, float(b) / 255);
    }

    bool pixel_to_entity_id(uint8_t* pixel, EntityID& res)
    {
        if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255) {
            return false;
        }
        res = ((size_t)pixel[0] << 16) + ((size_t)pixel[1] << 8) + ((size_t)pixel[2]);
        return true;
    }

    Generic::FramebufferIndex m_fb_index;
    EntityID m_cur_draw_entity_id;
    std::shared_ptr<Generic::Renderer> m_renderer;
    std::shared_ptr<Generic::Shader> m_mapper2d_shader;
    EntityID m_camera_entity_id;
    Camera m_camera;

    int m_mouse_x;
    int m_mouse_y;
    bool m_mouse_was_clicked { false };
};