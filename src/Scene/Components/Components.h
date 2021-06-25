#pragma once

#include <ECS/ECS.h>
#include <Math/Matrix4f.h>
#include <Model.h>
#include <memory>

class TransformComponent : public Component<TransformComponent> {
public:
    TransformComponent(const Math::Matrix4f& translation, const Math::Matrix4f& rotation, const Math::Matrix4f& scale)
        : m_translation(translation)
        , m_rotation(rotation)
        , m_scale(scale)
    {
        recalculate_transform_matrix();
    }

    inline void set_translation(const Math::Matrix4f& translation)
    {
        m_translation = translation;
        recalculate_transform_matrix();
    }

    inline void set_rotation(const Math::Matrix4f& rotation)
    {
        m_rotation = rotation;
        recalculate_transform_matrix();
    }

    inline void set_scale(const Math::Matrix4f& scale)
    {
        m_scale = scale;
        recalculate_transform_matrix();
    }

    inline Math::Matrix4f& transform() { return m_transform; }

private:
    inline void recalculate_transform_matrix()
    {
        m_transform = m_translation * m_rotation * m_scale;
    }

private:
    Math::Matrix4f m_translation {};
    Math::Matrix4f m_rotation {};
    Math::Matrix4f m_scale {};

    Math::Matrix4f m_transform {};
};

struct PureTransformComponent : public Component<PureTransformComponent> {
    PureTransformComponent(const Math::Vector3f& position, const Math::Vector3f& rotation, const Math::Vector3f& scale)
        : position(position)
        , rotation(rotation)
        , scale(scale)
    {
    }
    Math::Vector3f position {};
    Math::Vector3f rotation {};
    Math::Vector3f scale {};
};

struct ModelComponent : public Component<ModelComponent> {
    explicit ModelComponent(const std::string& name)
        : model(name)
    {
    }

    Model model;
};

struct ShaderComponent : public Component<ShaderComponent> {
    explicit ShaderComponent(const std::shared_ptr<Generic::Shader>& shader)
        : shader(shader)
    {
    }
    std::shared_ptr<Generic::Shader> shader;
};

struct CameraComponent : public Component<CameraComponent> {
    explicit CameraComponent(const Math::Vector3f& position, const Math::Vector3f& up, float yaw, float pitch)
        : position(position)
        , up(up)
        , yaw(yaw)
        , pitch(pitch)
    {
    }

    Math::Vector3f position;
    Math::Vector3f up;
    Math::Vector3f target {};
    float yaw;
    float pitch;
};

struct FocusableComponent : public Component<FocusableComponent> {
    explicit FocusableComponent(bool focused = false)
        : focused(focused)
    {
    }
    bool focused;
};