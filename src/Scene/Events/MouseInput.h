#pragma once

#include <Application/Events/MouseEvent.h>
#include <ECS/ECS.h>

struct MouseMoveInputEvent : public ECS::BaseEvent {
    MouseMoveInputEvent(const MouseMoveEvent& event)
        : ECS::BaseEvent(ECS::EventEnumerator<MouseMoveInputEvent>::ID)
        , event(event)
    {
    }
    ~MouseMoveInputEvent() = default;

    MouseMoveEvent event;
};

struct MouseButtonInputEvent : public ECS::BaseEvent {
    MouseButtonInputEvent(const BaseMouseButtonEvent& event)
        : ECS::BaseEvent(ECS::EventEnumerator<MouseButtonInputEvent>::ID)
        , event(event)
    {
    }
    ~MouseButtonInputEvent() = default;

    BaseMouseButtonEvent event;
};

struct MouseEntityClickEvent : public ECS::BaseEvent {
    MouseEntityClickEvent(ECS::EntityID entity_id)
        : ECS::BaseEvent(ECS::EventEnumerator<MouseEntityClickEvent>::ID)
        , entity_id(entity_id)
    {
    }
    ~MouseEntityClickEvent() = default;

    ECS::EntityID entity_id;
};