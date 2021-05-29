#include "Camera.h"
#include <Math/Matrix4f.h>

Camera::Camera(const Math::Vector3f& position, const Math::Vector3f& up, float yaw, float pitch)
    : m_position(position)
    , m_up(up)
    , m_yaw(yaw)
    , m_pitch(pitch)
{
    recalculate_target();
    recalculate_view_matrix();
}

void Camera::recalculate_view_matrix()
{
    m_view_matrix = Math::Matrix4f::LookAt(m_position, m_position + m_target, m_up);
}

void Camera::recalculate_target()
{
    m_target.set_z(cosf(m_yaw) * cosf(m_pitch));
    m_target.set_y(sinf(m_pitch));
    m_target.set_x(sinf(m_yaw) * cosf(m_pitch));
}