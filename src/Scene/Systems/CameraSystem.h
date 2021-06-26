#pragma once

#include <Config.h>
#include <ECS/ECS.h>
#include <Math/Vector3f.h>
#include <Scene/Events/KeyboardInput.h>
#include <Scene/Events/MouseInput.h>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

class CameraSystem : public ECS::System<Config::ComponentCount, Config::SystemCount> {
    static constexpr auto StepSize = 0.15f;

public:
    explicit CameraSystem(ECS::ECS<Config::ComponentCount, Config::SystemCount>* iecs)
        : ECS::System<Config::ComponentCount, Config::SystemCount>(iecs)
    {
        ecs().subscribe_for_events<KeyboardInputEvent>([this](const ECS::BaseEvent& event) { handle_callback(event); });
        ecs().subscribe_for_events<MouseMoveInputEvent>([this](const ECS::BaseEvent& event) { handle_callback(event); });
        ecs().subscribe_for_events<MouseButtonInputEvent>([this](const ECS::BaseEvent& event) { handle_callback(event); });

        set_required_components<CameraComponent, TransformComponent>();
    }

    void update() override
    {
        for (auto entity_id : m_managed_entities) {
            auto& transform_component = ecs().get_component<TransformComponent>(entity_id);

            auto& position = transform_component.position;

            float pitch = transform_component.rotation.x();
            float yaw = transform_component.rotation.y();
            auto target = transform_component.calc_target_vector();
            auto up = transform_component.calc_up_vector();

            if (m_w) {
                // Move forward
                transform_component.position += (target * StepSize);
            }
            if (m_s) {
                // Move back
                transform_component.position -= (target * StepSize);
            }
            if (m_a) {
                // Move left
                auto left = up.cross_product(target).normilize() * StepSize;
                transform_component.position += left;
            }
            if (m_d) {
                // Move right
                auto right = target.cross_product(up).normilize() * StepSize;
                transform_component.position += right;
            }
            if (m_horizontal_turn) {
                // Turn around Y
                transform_component.rotation.set_y(yaw + m_horizontal_turn);
                m_horizontal_turn = 0.0f;
            }
            if (m_vertical_turn) {
                // Turn around X
                auto new_pitch = pitch += m_vertical_turn;

                if (new_pitch > 3.0f / 2.0f) {
                    new_pitch = 3.0f / 2.0f;
                }
                if (new_pitch < -3.0f / 2.0f) {
                    new_pitch = -3.0f / 2.0f;
                }

                transform_component.rotation.set_x(new_pitch);
                m_vertical_turn = 0.0f;
            }
        }
    }

    void handle_callback(const ECS::BaseEvent& ecs_event)
    {
        if (ecs_event.id() == ECS::EventEnumerator<KeyboardInputEvent>::ID) {
            const BaseKeyboardEvent& event = ((const KeyboardInputEvent&)ecs_event).event;
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

        if (ecs_event.id() == ECS::EventEnumerator<MouseMoveInputEvent>::ID) {
            const MouseMoveEvent& mouse_event = ((const MouseMoveInputEvent&)ecs_event).event;
            if (!m_mouse_right_button_pressed) {
                return;
            }

            m_horizontal_turn = -Math::Numbers::pi_v<float> * mouse_event.x() / Config::SCREEN_WIDTH;
            m_vertical_turn = -Math::Numbers::pi_v<float> * mouse_event.y() / Config::SCREEN_HEIGHT;
        }

        if (ecs_event.id() == ECS::EventEnumerator<MouseButtonInputEvent>::ID) {
            const BaseMouseButtonEvent& mouse_event = ((const MouseButtonInputEvent&)ecs_event).event;
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

private:
    bool m_w { false };
    bool m_a { false };
    bool m_s { false };
    bool m_d { false };
    bool m_mouse_right_button_pressed { false };
    float m_horizontal_turn { 0.0f };
    float m_vertical_turn { 0.0f };
};