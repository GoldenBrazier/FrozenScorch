#include "Scene.h"
#include "Components/Components.h"
#include "Systems/RenderSystem.h"
#include <Application/Events/Event.h>
#include <Application/Events/KeyboardEvent.h>
#include <Application/Events/MouseEvent.h>
#include <GraphicsAPI/Generic/Constructors.h>
#include <Renderer/Renderer.h>
#include <Config.h>

void Scene::initialize()
{
    renderer = Constructors::Renderer::construct();
    m_shader = Ctx.shader_storage().get("basic_shader");

    m_ecs.register_component<TransformComponent>();
    m_ecs.register_component<ModelComponent>();
    m_ecs.register_component<ShaderComponent>();

    m_ecs.create_system<RenderSystem>(renderer, m_camera);

    // --------------- Demo entities ---------------
    float distance = 0;
    for (size_t i = 0; i < 4; i++) {
        auto entity = m_ecs.create_entity(i % 2 ? "water_tower " : "crate ");

        auto translation = Math::Matrix4f::Translation({ distance, 0, 0 });
        auto rotation = Math::Matrix4f::RotationAroundZ(0);
        auto scale = Math::Matrix4f::Scaling(1);

        m_ecs.add_component<TransformComponent>(entity, translation, rotation, scale);
        m_ecs.add_component<ModelComponent>(entity, i % 2 ? "water_tower" : "crate");
        m_ecs.add_component<ShaderComponent>(entity, m_shader);

        distance += 10;
    }
    // ---------------------------------------------
}

void Scene::update()
{
    if (w) {
        m_camera.move_forward();
    }
    if (a) {
        m_camera.move_left();
    }
    if (s) {
        m_camera.move_backward();
    }
    if (d) {
        m_camera.move_right();
    }

    m_ecs.update_systems();
}

void Scene::on_event(const Event& event)
{
    if (event.type() == EventType::KeyboardPressed) {
        auto& keyboard_event = (KeyboardPressedEvent&)(event);
        if (keyboard_event.key() == OpenRenderer::KEYCODE_W) {
            w = true;
        }
        if (keyboard_event.key() == OpenRenderer::KEYCODE_S) {
            s = true;
        }
        if (keyboard_event.key() == OpenRenderer::KEYCODE_A) {
            a = true;
        }
        if (keyboard_event.key() == OpenRenderer::KEYCODE_D) {
            d = true;
        }
    }

    if (event.type() == EventType::KeyboardReleased) {
        auto& keyboard_event = (KeyboardPressedEvent&)(event);
        if (keyboard_event.key() == OpenRenderer::KEYCODE_W) {
            w = false;
        }
        if (keyboard_event.key() == OpenRenderer::KEYCODE_S) {
            s = false;
        }
        if (keyboard_event.key() == OpenRenderer::KEYCODE_A) {
            a = false;
        }
        if (keyboard_event.key() == OpenRenderer::KEYCODE_D) {
            d = false;
        }
    }

    if (event.type() == EventType::MouseMove) {
        if (!m_mouse_right_button_pressed) {
            return;
        }

        auto& mouse_event = (MouseMoveEvent&)(event);

        float horizontal_turn = -Math::Numbers::pi_v<float> * mouse_event.x() / Config::SCREEN_WIDTH;
        float vertical_turn = -Math::Numbers::pi_v<float> * mouse_event.y() / Config::SCREEN_HEIGHT;

        m_camera.turn_horizontally(horizontal_turn);
        m_camera.turn_vertically(vertical_turn);
    }

    if (event.type() == EventType::MouseButtonReleased) {
        auto& mouse_event = (MouseButtonReleasedEvent&)(event);
        if (mouse_event.button() == MouseCode::RightButton) {
            m_mouse_right_button_pressed = false;
        }
    }

    if (event.type() == EventType::MouseButtonPressed) {
        auto& mouse_event = (MouseButtonPressedEvent&)(event);
        if (mouse_event.button() == MouseCode::RightButton) {
            m_mouse_right_button_pressed = true;
        }
    }
}
