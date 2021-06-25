#pragma once

#include <Application/Camera.h>
#include <Application/Events/Event.h>
#include <Config.h>
#include <ECS/ECS.h>
#include <Math/Matrix4f.h>
#include <Renderer/Renderer.h>
#include <memory>

class Scene {
public:
    Scene() = default;

    void initialize();
    void update();
    void on_event(const Event& event);

    inline auto& ecs() { return m_ecs; }

private:
    std::shared_ptr<Generic::Renderer> renderer {};
    std::shared_ptr<Generic::Shader> m_shader {};

    ECS<Config::ComponentCount, Config::SystemCount> m_ecs;
    Camera m_camera { Camera({ 0, 0, 0 }, { 0, 1, 0 }) };
};
