#pragma once

class Vector3f final {
public:
    Vector3f(float x, float y, float z)
        : m_x(x)
        , m_y(y)
        , m_z(z)
    {
    }

    inline Vector3f& operator+=(const Vector3f& vector);
    inline Vector3f& operator-=(const Vector3f& vector);
    inline Vector3f& operator*=(float f);

    inline Vector3f cross(const Vector3f& vector);

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
    m_x += vector.m_x;
    m_y += vector.m_y;
    m_z += vector.m_z;

    return *this;
}

Vector3f& Vector3f::operator*=(float f)
{
    m_x *= f;
    m_y *= f;
    m_z *= f;

    return *this;
}

Vector3f Vector3f::cross(const Vector3f& vector)
{
    return Vector3f(m_x * vector.m_x, m_y * vector.m_y, m_z * vector.m_z);
}