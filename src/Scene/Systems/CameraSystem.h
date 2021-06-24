#pragma once

#include <Config.h>
#include <ECS/ECS.h>
#include <Scene/Events/KeyboardInput.h>
#include <Scene/Events/MouseInput.h>
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
        ecs().subscribe_for_events<MouseMoveInputEvent>([this](std::unique_ptr<BaseEvent> event) { handle_callback(std::move(event)); });
        ecs().subscribe_for_events<MouseButtonInputEvent>([this](std::unique_ptr<BaseEvent> event) { handle_callback(std::move(event)); });
    }

    void update() override
    {
        for (auto entity_id : m_managed_entities) {
            auto& position_component = ecs().get_component<CameraComponent>(entity_id);
            if (m_w) {
                move_forward(position_component);
            }
            if (m_a) {
                move_left(position_component);
            }
            if (m_s) {
                move_backward(position_component);
            }
            if (m_d) {
                move_right(position_component);
            }
            if (m_horizontal_turn) {
                turn_horizontally(position_component, m_horizontal_turn);
                m_horizontal_turn = 0.0f;
            }
            if (m_vertical_turn) {
                turn_vertically(position_component, m_vertical_turn);
                m_vertical_turn = 0.0f;
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
                    m_w = true;
                }
                if (keyboard_event.key() == OpenRenderer::KEYCODE_S) {
                    m_s = true;
                }
                if (keyboard_event.key() == OpenRenderer::KEYCODE_A) {
                    m_a = true;
                }
                if (keyboard_event.key() == OpenRenderer::KEYCODE_D) {
                    m_d = true;
                }
            }

            if (event.type() == EventType::KeyboardReleased) {
                auto& keyboard_event = event;
                if (keyboard_event.key() == OpenRenderer::KEYCODE_W) {
                    m_w = false;
                }
                if (keyboard_event.key() == OpenRenderer::KEYCODE_S) {
                    m_s = false;
                }
                if (keyboard_event.key() == OpenRenderer::KEYCODE_A) {
                    m_a = false;
                }
                if (keyboard_event.key() == OpenRenderer::KEYCODE_D) {
                    m_d = false;
                }
            }
        }

        if (ecs_event->id() == EventEnumerator<MouseMoveInputEvent>::ID) {
            const MouseMoveEvent& mouse_event = ((MouseMoveInputEvent*)(ecs_event.get()))->event;
            if (!m_mouse_right_button_pressed) {
                return;
            }

            m_horizontal_turn = -Math::Numbers::pi_v<float> * mouse_event.x() / Config::SCREEN_WIDTH;
            m_vertical_turn = -Math::Numbers::pi_v<float> * mouse_event.y() / Config::SCREEN_HEIGHT;
        }

        if (ecs_event->id() == EventEnumerator<MouseButtonInputEvent>::ID) {
            const BaseMouseButtonEvent& mouse_event = ((MouseButtonInputEvent*)(ecs_event.get()))->event;
            if (mouse_event.type() == EventType::MouseButtonPressed) {
                if (mouse_event.button() == MouseCode::RightButton) {
                    m_mouse_right_button_pressed = true;
                }
            }
            if (mouse_event.type() == EventType::MouseButtonReleased) {
                if (mouse_event.button() == MouseCode::RightButton) {
                    m_mouse_right_button_pressed = false;
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

    inline void turn_horizontally(CameraComponent& component, float angle)
    {
        component.yaw += angle;
        recalculate_target(component);
    }

    inline void turn_vertically(CameraComponent& component, float angle)
    {
        component.pitch += angle;

        if (component.pitch > 3.0f / 2.0f) {
            component.pitch = 3.0f / 2.0f;
        }
        if (component.pitch < -3.0f / 2.0f) {
            component.pitch = -3.0f / 2.0f;
        }

        recalculate_target(component);
    }

    inline void recalculate_target(CameraComponent& component)
    {
        component.target.set_z(cosf(component.yaw) * cosf(component.pitch));
        component.target.set_y(sinf(component.pitch));
        component.target.set_x(sinf(component.yaw) * cosf(component.pitch));
    }

private:
    bool m_w { false };
    bool m_a { false };
    bool m_s { false };
    bool m_d { false };
    bool m_mouse_right_button_pressed { false };
    float m_horizontal_turn { 0.0f };
    float m_vertical_turn { 0.0f };
};