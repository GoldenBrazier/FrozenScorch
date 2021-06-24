#include "Editor.h"
#include <Config.h>
#include <GraphicsAPI/Generic/Context.h>
#include <GraphicsAPI/Generic/Display.h>
#include <GraphicsAPI/OpenGL/Display.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

void Editor::init(const std::shared_ptr<Generic::Display>& display, Scene& scene)
{
    if (Ctx.graphics_api_type() != Generic::GraphicsAPIType::OpenGL) {
        std::abort();
    }

    scene_ptr = &scene;
    display_ptr = display;

    auto context = Ctx.opengl_context()->sdl_glcontext();
    auto window = std::static_pointer_cast<GL::Display>(display_ptr)->window();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init(Config::GLSL_VERSION);

    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    m_scene_panel.init(scene);
}

void Editor::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Editor::draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(std::static_pointer_cast<GL::Display>(display_ptr)->window());
    ImGui::NewFrame();

    // Don't delete these lines please
//    static bool show_demo = true;
//    ImGui::ShowDemoWindow(&show_demo);

    m_scene_panel.draw();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
