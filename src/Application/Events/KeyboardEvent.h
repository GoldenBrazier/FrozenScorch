#pragma once

#include "Event.h"
#include <Application/KeyCodes.h>

class BaseKeyboardEvent : public Event {
public:
    BaseKeyboardEvent(EventType type, OpenRenderer::KeyCode key)
        : Event(type)
        , m_key(key)
    {
    }

    OpenRenderer::KeyCode key() const { return m_key; }

private:
    OpenRenderer::KeyCode m_key;
};

template <EventType T>
class KeyboardEvent : public BaseKeyboardEvent {
public:
    KeyboardEvent(OpenRenderer::KeyCode key)
        : BaseKeyboardEvent(T, key)
    {
    }
};

using KeyboardPressedEvent = KeyboardEvent<EventType::KeyboardPressed>;
using KeyboardReleasedEvent = KeyboardEvent<EventType::KeyboardReleased>;
using KeyboardRepeateEvent = KeyboardEvent<EventType::KeyboardRepeate>;