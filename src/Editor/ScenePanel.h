#pragma once

#include <ECS/ECS.h>
#include <Scene/Events/MouseInput.h>
#include <Scene/Scene.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

class ScenePanel {
public:
    inline void init(Scene& scene)
    {
        scene_ptr = &scene;
        scene.ecs().subscribe_for_events<MouseEntityClickEvent>([this](const ECS::BaseEvent& event) { handle_callback(event); });
    }

    void draw();

private:
    void draw_entity_picker();
    void draw_components();
    void handle_callback(const ECS::BaseEvent& event);
    void set_focus_on_entity(ECS::EntityID entity_id);

    inline Scene& scene() { return *scene_ptr; }

    Scene* scene_ptr {};
    size_t m_cur_entity {};
    Math::Vector3f m_position {};
};
