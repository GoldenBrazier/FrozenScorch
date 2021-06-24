#pragma once

#include <Scene/Scene.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <iostream>

class ScenePanel {
public:
    inline void init(Scene& scene)
    {
        scene_ptr = &scene;
    }

    void draw();

private:
    inline Scene& scene() { return *scene_ptr; }

private:
    Scene* scene_ptr {};
};
