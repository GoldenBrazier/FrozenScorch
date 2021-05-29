#pragma once

#include <Math/Matrix4f.h>
#include <Math/Vector3f.h>

class Camera {
public:
    Camera(const Math::Vector3f& position, const Math::Vector3f& up, float yaw = 0, float pitch = 0);

public:
    inline const Math::Matrix4f& view_matrix() const { return m_view_matrix; }

    inline void move_forward(float step_size = 1)
    {
        m_position += (m_target * step_size);
        recalculate_view_matrix();
    }

    inline void move_backward(float step_size = 1)
    {
        m_position -= (m_target * step_size);
        recalculate_view_matrix();
    }

    inline void move_left(float step_size = 1)
    {
        auto left = m_target.cross_product(m_up).normilize() * step_size;
        m_position += left;
        recalculate_view_matrix();
    }

    inline void move_right(float step_size = 1)
    {
        auto right = m_up.cross_product(m_target).normilize() * step_size;
        m_position += right;
        recalculate_view_matrix();
    }

    inline void turn_horizontally(float angle)
    {
        m_yaw += angle;
        recalculate_target();
        recalculate_view_matrix();
    }

    inline void turn_vertically(float angle)
    {
        m_pitch += angle;

        if (m_pitch > 3.0f / 2.0f) {
            m_pitch = 3.0f / 2.0f;
        }
        if (m_pitch < -3.0f / 2.0f) {
            m_pitch = -3.0f / 2.0f;
        }

        recalculate_target();
        recalculate_view_matrix();
    }

private:
    void recalculate_view_matrix();
    void recalculate_target();

private:
    Math::Vector3f m_position;
    Math::Vector3f m_up;

    float m_yaw;
    float m_pitch;

    Math::Vector3f m_target {};
    Math::Matrix4f m_view_matrix;
};