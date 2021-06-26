#pragma once

#include <ECS/ECS.h>
#include <Math/Matrix4f.h>
#include <Model.h>
#include <memory>

struct TransformComponent : public ECS::Component<TransformComponent> {
    TransformComponent(const Math::Vector3f& position, const Math::Vector3f& rotation, const Math::Vector3f& scale)
        : position(position)
        , rotation(rotation)
        , scale(scale)
    {
    }
    Math::Vector3f position {};
    Math::Vector3f rotation {};
    Math::Vector3f scale {};

    // Helper functions that do not modify state of the component
    // They are used to reduce code repetitions
    inline Math::Vector3f calc_target_vector() const
    {
        return Math::Vector3f(sinf(rotation.y()) * cosf(rotation.x()), sinf(rotation.x()), cosf(rotation.y()) * cosf(rotation.x()));
    }

    inline Math::Vector3f calc_up_vector() const
    {
        return Math::Vector3f(sinf(rotation.z()), cosf(rotation.z()), 0);
    }

    inline Math::Matrix4f calc_view_matrix() const
    {
        return Math::Matrix4f::LookAt(position, position + calc_target_vector(), calc_up_vector());
    }
};

struct ModelComponent : public ECS::Component<ModelComponent> {
    explicit ModelComponent(const std::string& name)
        : model(name)
    {
    }

    Model model;
};

struct ShaderComponent : public ECS::Component<ShaderComponent> {
    explicit ShaderComponent(const std::shared_ptr<Generic::Shader>& shader)
        : shader(shader)
    {
    }
    std::shared_ptr<Generic::Shader> shader;
};

struct CameraComponent : public ECS::Component<CameraComponent> {
    CameraComponent(float field_of_view, float near_clipping, float far_clipping)
        : field_of_view(field_of_view)
        , near_clipping(near_clipping)
        , far_clipping(far_clipping)
    {
    }

    float field_of_view;
    float near_clipping;
    float far_clipping;
};

struct FocusableComponent : public ECS::Component<FocusableComponent> {
    explicit FocusableComponent(bool focused = false)
        : focused(focused)
    {
    }
    bool focused;
};
