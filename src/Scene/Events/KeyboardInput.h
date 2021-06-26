#pragma once

#include <Application/Events/KeyboardEvent.h>
#include <ECS/ECS.h>

struct KeyboardInputEvent : public ECS::BaseEvent {
    KeyboardInputEvent(const BaseKeyboardEvent& event)
        : ECS::BaseEvent(ECS::EventEnumerator<KeyboardInputEvent>::ID)
        , event(event)
    {
    }
    ~KeyboardInputEvent() = default;

    BaseKeyboardEvent event;
};