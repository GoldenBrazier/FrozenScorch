#pragma once

#include <cstddef>
#include <cstdint>

template <typename T>
struct EventEnumerator {
    static const size_t ID;
};

inline size_t generate_event_type()
{
    static size_t counter = 0;
    return counter++;
}

template <typename T>
const size_t EventEnumerator<T>::ID = generate_event_type();

class BaseEvent {
public:
    BaseEvent(const size_t id)
        : m_id(id)
    {
    }

    size_t id() const { return m_id; }

private:
    size_t m_id;
};