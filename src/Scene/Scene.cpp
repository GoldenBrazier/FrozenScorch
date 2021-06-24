#include "Scene.h"
#include "Components/Components.h"
#include "Events/KeyboardInput.h"
#include "Systems/CameraSystem.h"
#include "Systems/RenderSystem.h"
#include <Application/Events/Event.h>
#include <Application/Events/KeyboardEvent.h>
#include <Application/Events/MouseEvent.h>
#include <Config.h>
#include <GraphicsAPI/Generic/Constructors.h>
#include <Renderer/Renderer.h>

void Scene::initialize()
{
    renderer = Constructors::Renderer::construct();
    m_shader = Ctx.shader_storage().get("basic_shader");

    m_ecs.register_component<PureTransformComponent>();
    m_ecs.register_component<ModelComponent>();
    m_ecs.register_component<ShaderComponent>();
    m_ecs.register_component<CameraComponent>();

    m_ecs.create_system<CameraSystem>();

    // FIXME: Now we can't create systems after entities.
    auto camera_entity = m_ecs.create_entity("camera");
    m_ecs.add_component<CameraComponent>(camera_entity, Math::Vector3f({ 0, 0, 0 }), Math::Vector3f({ 0, 1, 0 }), 0.0f, 0.0f);
    m_ecs.create_system<RenderSystem>(renderer, camera_entity);

    // --------------- Demo entities ---------------
    float distance = 0;
    for (size_t i = 0; i < 4; i++) {
        auto entity = m_ecs.create_entity(i % 2 ? "water_tower " : "crate ");

        auto position = Math::Vector3f(distance, 0, 0);
        auto rotation = Math::Vector3f(0, 0, 0);
        auto scale = Math::Vector3f(1, 1, 1);

        m_ecs.add_component<PureTransformComponent>(entity, position, rotation, scale);
        m_ecs.add_component<ModelComponent>(entity, i % 2 ? "water_tower" : "crate");
        m_ecs.add_component<ShaderComponent>(entity, m_shader);

        distance += 10;
    }
    // ---------------------------------------------
}

void Scene::update()
{
    m_ecs.dispatch_events();
    m_ecs.update_systems();
}

void Scene::on_event(const Event& event)
{
    if (event.type() == EventType::KeyboardPressed || event.type() == EventType::KeyboardReleased || event.type() == EventType::KeyboardRepeate) {
        auto& keyboard_event = (BaseKeyboardEvent&)(event);
        m_ecs.post_event<KeyboardInputEvent>(keyboard_event);
        return;
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
