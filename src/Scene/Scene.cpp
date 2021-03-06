#include "Scene.h"
#include "Components/Components.h"
#include "Events/KeyboardInput.h"
#include "Systems/CameraSystem.h"
#include "Systems/MouseRayCastingSystem.h"
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
    m_mapper2d_shader = Ctx.shader_storage().get("mapper2d_shader");

    m_ecs.register_component<TransformComponent>();
    m_ecs.register_component<ModelComponent>();
    m_ecs.register_component<ShaderComponent>();
    m_ecs.register_component<CameraComponent>();
    m_ecs.register_component<FocusableComponent>();

    auto camera_entity = m_ecs.create_entity("camera");

    auto camera_position = Math::Vector3f(0, 0, 0);
    auto camera_rotation = Math::Vector3f(0, 0, 0);
    auto camera_scale = Math::Vector3f(1, 1, 1);

    m_ecs.add_component<TransformComponent>(camera_entity, camera_position, camera_rotation, camera_scale);
    m_ecs.add_component<CameraComponent>(camera_entity, 90, 0.01f, 1000);

    m_ecs.create_system<CameraSystem>();
    m_ecs.create_system<RenderSystem>(renderer, camera_entity);
    m_ecs.create_system<MouseRayCastingSystem>(renderer, m_mapper2d_shader, camera_entity);

    // --------------- Demo entities ---------------
    float distance = 0;
    for (size_t i = 0; i < 4; i++) {
        auto entity = m_ecs.create_entity(i % 2 ? "water_tower " : "crate ");

        auto position = Math::Vector3f(distance, 0, 0);
        auto rotation = Math::Vector3f(0, 0, 0);
        auto scale = Math::Vector3f(1, 1, 1);

        m_ecs.add_component<TransformComponent>(entity, position, rotation, scale);
        m_ecs.add_component<ModelComponent>(entity, i % 2 ? "water_tower" : "crate");
        m_ecs.add_component<ShaderComponent>(entity, m_shader);
        m_ecs.add_component<FocusableComponent>(entity, false);

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
        auto& mouse_event = (MouseMoveEvent&)(event);
        m_ecs.post_event<MouseMoveInputEvent>(mouse_event);
    }

    if (event.type() == EventType::MouseButtonPressed || event.type() == EventType::MouseButtonReleased) {
        auto& mouse_event = (BaseMouseButtonEvent&)(event);
        m_ecs.post_event<MouseButtonInputEvent>(mouse_event);
    }
}
