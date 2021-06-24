#pragma once

#include <Application/Events/MouseEvent.h>
#include <ECS/ECS.h>

struct MouseMoveInputEvent : public BaseEvent {
    MouseMoveInputEvent(const MouseMoveEvent& event)
        : BaseEvent(EventEnumerator<MouseMoveInputEvent>::ID)
        , event(event)
    {
    }
    ~MouseMoveInputEvent() = default;

    MouseMoveEvent event;
};

struct MouseButtonInputEvent : public BaseEvent {
    MouseButtonInputEvent(const BaseMouseButtonEvent& event)
        : BaseEvent(EventEnumerator<MouseButtonInputEvent>::ID)
        , event(event)
    {
    }
    ~MouseButtonInputEvent() = default;

    BaseMouseButtonEvent event;
};