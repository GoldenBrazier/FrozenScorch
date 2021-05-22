#pragma once

#include "Event.h"
#include <stdint.h>

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(uint32_t width, uint32_t height)
        : Event(EventType::WindowResize)
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

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent()
        : Event(EventType::WindowClose)
    {
    }
};