#pragma once
#include <Utils.h>

#include <cmath>

namespace Math {

class PACKED Vector3f final {
public:
    Vector3f() = default;
    Vector3f(float x, float y, float z)
        : m_x(x)
        , m_y(y)
        , m_z(z)
    {
    }

    inline float x() const { return m_x; }
    inline void set_x(float x) { m_x = x; }

    inline float y() const { return m_y; }
    inline void set_y(float y) { m_y = y; }

    inline float z() const { return m_z; }
    inline void set_z(float z) { m_z = z; }

    inline Vector3f& operator+=(const Vector3f& vector);
    inline Vector3f& operator-=(const Vector3f& vector);
    inline Vector3f& operator*=(float f);

    friend Vector3f operator*(const Vector3f& vector, float value);
    friend Vector3f operator+(const Vector3f& l, const Vector3f& r);
    friend Vector3f operator-(const Vector3f& l, const Vector3f& r);

    inline Vector3f cross_product(const Vector3f& vector) const;
    inline float dot_product(const Vector3f& vector) const;
    inline Vector3f normilize() const;

    inline float length() const;

private:
    float m_x {};
    float m_y {};
    float m_z {};
};

Vector3f& Vector3f::operator+=(const Vector3f& vector)
{
    m_x += vector.m_x;
    m_y += vector.m_y;
    m_z += vector.m_z;

    return *this;
}

Vector3f& Vector3f::operator-=(const Vector3f& vector)
{
    m_x -= vector.m_x;
    m_y -= vector.m_y;
    m_z -= vector.m_z;

    return *this;
}

Vector3f& Vector3f::operator*=(float f)
{
    m_x *= f;
    m_y *= f;
    m_z *= f;

    return *this;
}

Vector3f Vector3f::cross_product(const Vector3f& vector) const
{
    return Vector3f(
        m_y * vector.m_z - m_z * vector.m_y,
        m_z * vector.m_x - m_x * vector.m_z,
        m_x * vector.m_y - m_y * vector.m_x);
}

float Vector3f::dot_product(const Vector3f& v) const
{
    return m_x * v.x() + m_y * v.y() + m_z * v.z();
}

Vector3f Vector3f::normilize() const
{
    float len = length();
    return { m_x / len, m_y / len, m_z / len };
}

float Vector3f::length() const
{
    return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
}

}