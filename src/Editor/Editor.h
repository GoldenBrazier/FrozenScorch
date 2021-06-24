#pragma once

#include <GraphicsAPI/Generic/Display.h>
#include <Scene/Scene.h>
#include "ScenePanel.h"

class Editor {
public:
    Editor() = default;
    void init(const std::shared_ptr<Generic::Display>& display, Scene& scene);
    void shutdown();
    void draw();

private:
    inline Scene& scene() { return *scene_ptr; }

private:
    Scene* scene_ptr {};
    std::shared_ptr<Generic::Display> display_ptr {};
    ScenePanel m_scene_panel;
};
