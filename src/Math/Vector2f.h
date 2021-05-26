#pragma once
#include <Utils.h>

namespace Math {

class PACKED Vector2f final {
public:
    Vector2f(float x, float y)
        : m_x(x)
        , m_y(y)
    {
    }

    inline float x() const { return m_x; }
    inline float y() const { return m_y; }

    inline Vector2f& operator+=(const Vector2f& vector);
    inline Vector2f& operator-=(const Vector2f& vector);
    inline Vector2f& operator*=(float f);

private:
    float m_x {};
    float m_y {};
};

Vector2f& Vector2f::operator+=(const Vector2f& vector)
{
    m_x += vector.m_x;
    m_y += vector.m_y;

    return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& vector)
{
    m_x += vector.m_x;
    m_y += vector.m_y;

    return *this;
}

Vector2f& Vector2f::operator*=(float f)
{
    m_x *= f;
    m_y *= f;

    return *this;
}

}