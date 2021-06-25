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

struct MouseEntityClickEvent : public BaseEvent {
    MouseEntityClickEvent(EntityID entity_id)
        : BaseEvent(EventEnumerator<MouseEntityClickEvent>::ID)
        , entity_id(entity_id)
    {
    }
    ~MouseEntityClickEvent() = default;

    EntityID entity_id;
};