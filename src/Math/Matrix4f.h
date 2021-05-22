#pragma once
#include <Math/Trigonometry.h>
#include <Math/Vector3f.h>
#include <array>
#include <cmath>

namespace Math {

class Matrix4f {
public:
    using DataType = std::array<float, 16>;

public:
    explicit Matrix4f(const DataType& data)
        : m_data(data)
    {
    }

public:
    inline float* data() { return m_data.data(); }
    inline const float* data() const { return m_data.data(); }

public:
    inline float* operator[](std::size_t row) { return m_data.data() + row * 4 * sizeof(float); }
    inline const float* operator[](std::size_t row) const { return m_data.data() + row * 4; }

    inline Matrix4f& operator*=(const Matrix4f& mat);

public:
    static inline Matrix4f Translation(const Vector3f& vec);
    static inline Matrix4f RotationAroundX(float radians);
    static inline Matrix4f RotationAroundY(float radians);
    static inline Matrix4f RotationAroundZ(float radians);
    static inline Matrix4f Scaling(float scale);
    static inline Matrix4f Perspective(float width, float height, float zNear, float zFar, float angle);

private:
    std::array<float, 16> m_data;
};

Matrix4f& Matrix4f::operator*=(const Matrix4f& matrix)
{
    for (std::size_t row = 0; row < 4; row++) {
        for (std::size_t col = 0; col < 4; col++) {
            float dot_product = 0;
            for (std::size_t i = 0; i < 4; i++) {
                dot_product += (*this[row][i] * matrix[i][col]);
            }
            *this[row][col] = dot_product;
        }
    }
    return *this;
}

// clang-format off
Matrix4f Matrix4f::Translation(const Vector3f& vec)
{
    return Matrix4f({
        1, 0, 0, vec.x(),
        0, 1, 0, vec.y(),
        0, 0, 1, vec.z(),
        0, 0, 0, 1,
    });
}

Matrix4f Matrix4f::RotationAroundX(float radians)
{
    return Matrix4f({
        1, 0, 0, 0,
        0, cosf(radians), -sinf(radians), 0,
        0, sinf(radians), cosf(radians), 0,
        0, 0, 0, 1,
    });
}

Matrix4f Matrix4f::RotationAroundY(float radians)
{
    return Matrix4f({
        cosf(radians), 0, -sinf(radians), 0,
        0, 1, 0, 0,
        sinf(radians), 0, cosf(radians), 0,
        0, 0, 0, 1,
    });
}

Matrix4f Matrix4f::RotationAroundZ(float radians)
{
    return Matrix4f({
        cosf(radians), -sinf(radians), 0, 0,
        sinf(radians), cosf(radians), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    });
}

Matrix4f Matrix4f::Scaling(float scale)
{
    return Matrix4f({
        sinf(scale), 0, 0, 0,
        0, sinf(scale), 0, 0,
        0, 0, sinf(scale), 0,
        0, 0, 0, 1,
    });
}

Matrix4f Matrix4f::Perspective(float width, float height, float near_z, float far_z, float view_angle)
{
    float view_angle_rect_tan = tanf(deg_to_rad(view_angle / 2.0f));
    float display_aspect_ratio = width / height;
    return Matrix4f({
        (1.0f / (view_angle_rect_tan * display_aspect_ratio)), 0, 0, 0,
        0, (1.0f / view_angle_rect_tan), 0, 0,
        0, 0, ((-near_z - far_z) / (near_z - far_z)), (2.0f * far_z * near_z / (near_z - far_z)),
        0, 0, 1.0f, 0,
    });
}
// clang-format on

}