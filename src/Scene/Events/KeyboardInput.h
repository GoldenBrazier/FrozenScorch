#pragma once

#include <Application/Events/KeyboardEvent.h>
#include <ECS/ECS.h>

struct KeyboardInputEvent : public BaseEvent {
    KeyboardInputEvent(const BaseKeyboardEvent& event)
        : BaseEvent(EventEnumerator<KeyboardInputEvent>::ID)
        , event(event)
    {
    }
    ~KeyboardInputEvent() = default;

    BaseKeyboardEvent event;
};