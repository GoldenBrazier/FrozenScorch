#pragma once

#include "Event.h"
#include <stdint.h>

class MouseScrollEvent : public Event {
public:
    MouseScrollEvent(uint32_t width, uint32_t height)
        : Event(EventType::MouseScroll)
        , m_width(width)
        , m_height(height)
    {
    }

    uint32_t widht() const { return m_width; }
    uint32_t height() const { return m_height; }

private:
    uint32_t m_width;
    uint32_t m_height;
};

class MouseMoveEvent : public Event {
public:
    MouseMoveEvent(uint32_t x, uint32_t y)
        : Event(EventType::MouseMove)
        , m_x(x)
        , m_y(y)
    {
    }

    uint32_t x() const { return m_x; }
    uint32_t y() const { return m_y; }

private:
    uint32_t m_x;
    uint32_t m_y;
};

enum class MouseCode {};

template <EventType T>
class MouseButtonEvent : public Event {
public:
    MouseButtonEvent(MouseCode code)
        : Event(T)
        , m_code(code)
    {
    }

    MouseCode button() const { return m_code; }

private:
    MouseCode m_code;
};

using MouseButtonPressedEvent = MouseButtonEvent<EventType::MouseButtonPressed>;
using MouseButtonReleasedEvent = MouseButtonEvent<EventType::MouseButtonReleased>;
using MouseButtonRepeateEvent = MouseButtonEvent<EventType::MouseButtonRepeate>;