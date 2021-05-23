#pragma once

#include "Event.h"
#include <Application/KeyCodes.h>

template <EventType T>
class KeyboardEvent : public Event {
public:
    KeyboardEvent(OpenRenderer::KeyCode key)
        : Event(T)
    {
    }

    OpenRenderer::KeyCode key() const { return m_key; }

private:
    OpenRenderer::KeyCode m_key;
};

using KeyboardPressedEvent = KeyboardEvent<EventType::KeyboardPressed>;
using KeyboardReleasedEvent = KeyboardEvent<EventType::KeyboardReleased>;
using KeyboardRepeateEvent = KeyboardEvent<EventType::KeyboardRepeate>;