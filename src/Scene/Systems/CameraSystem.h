#pragma once

#include <Config.h>
#include <ECS/ECS.h>
#include <Scene/Events/KeyboardInput.h>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

class CameraSystem : public System<Config::ComponentCount, Config::SystemCount> {
public:
    explicit CameraSystem(ECS<Config::ComponentCount, Config::SystemCount>* iecs)
        : System<Config::ComponentCount, Config::SystemCount>(iecs)
    {
        set_required_components<CameraComponent>();
        ecs().subscribe_for_events<KeyboardInputEvent>([this](std::unique_ptr<BaseEvent> event) { handle_callback(std::move(event)); });
    }

    void update() override
    {
        // std::cout << "called " <<  std::endl;
        for (auto entity_id : m_managed_entities) {
            auto& position_component = ecs().get_component<CameraComponent>(entity_id);
            if (w) {
                move_forward(position_component);
            }
            if (a) {
                move_left(position_component);
            }
            if (s) {
                move_backward(position_component);
            }
            if (d) {
                move_right(position_component);
            }
        }
    }

    void handle_callback(std::unique_ptr<BaseEvent> ecs_event)
    {
        if (ecs_event->id() == EventEnumerator<KeyboardInputEvent>::ID) {
            const BaseKeyboardEvent& event = ((KeyboardInputEvent*)(ecs_event.get()))->event;
            if (event.type() == EventType::KeyboardPressed) {
                auto& keyboard_event = event;
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
                auto& keyboard_event = event;
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
        }
    }

    inline void move_forward(CameraComponent& component, float step_size = 0.15f)
    {
        component.position += (component.target * step_size);
        recalculate_target(component);
    }

    inline void move_backward(CameraComponent& component, float step_size = 0.15f)
    {
        component.position -= (component.target * step_size);
        recalculate_target(component);
    }

    inline void move_left(CameraComponent& component, float step_size = 0.15f)
    {
        auto left = component.up.cross_product(component.target).normilize() * step_size;
        component.position += left;
        recalculate_target(component);
    }

    inline void move_right(CameraComponent& component, float step_size = 0.15f)
    {
        auto right = component.target.cross_product(component.up).normilize() * step_size;
        component.position += right;
        recalculate_target(component);
    }

    inline void recalculate_target(CameraComponent& component)
    {
        component.target.set_z(cosf(component.yaw) * cosf(component.pitch));
        component.target.set_y(sinf(component.pitch));
        component.target.set_x(sinf(component.yaw) * cosf(component.pitch));
    }

private:
    bool w, a, s, d; // input system
    // bool m_mouse_right_button_pressed { false }; // input system
};