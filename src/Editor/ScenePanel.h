#pragma once

#include <Scene/Scene.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

class ScenePanel {
public:
    inline void init(Scene& scene)
    {
        scene_ptr = &scene;
    }

    void draw();

private:
    void draw_entity_picker();
    void draw_components();

    inline Scene& scene() { return *scene_ptr; }

private:
    Scene* scene_ptr {};

    size_t m_cur_entity {};
    Math::Vector3f m_position {};
};
