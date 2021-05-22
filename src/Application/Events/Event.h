#pragma once

enum class EventType {
    // Keyboard
    KeyboardPressed,
    KeyboardReleased,
    KeyboardRepeate,

    // Mouse events
    MouseScroll,
    MouseMove,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseButtonRepeate,

    // Window events
    WindowResize,
    WindowClose,
};

class Event {
public:
    Event(EventType type)
        : m_type(type)
    {
    }

    EventType type() const { return m_type; }

private:
    EventType m_type;
};