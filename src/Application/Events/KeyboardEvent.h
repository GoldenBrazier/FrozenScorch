#pragma once

#include "Event.h"

enum class Key {};

template <EventType T>
class KeyboardEvent : public Event {
public:
    KeyboardEvent(Key key)
        : Event(T)
    {
    }

    Key key() const { return m_key; }

private:
    Key m_key;
};

using KeyboardPressedEvent = KeyboardEvent<EventType::KeyboardPressed>;
using KeyboardReleasedEvent = KeyboardEvent<EventType::KeyboardReleased>;
using KeyboardRepeateEvent = KeyboardEvent<EventType::KeyboardRepeate>;