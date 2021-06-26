#include "ScenePanel.h"
#include <GraphicsAPI/Generic/Constructors.h>
#include <Scene/Components/Components.h>

static char model_path[256];
static char model_texture_path[256]; // TODO: Temprary

void ScenePanel::draw()
{
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", nullptr, window_flags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        static auto first_time = true;
        if (first_time) {
            first_time = false;

            ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
            ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

            auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dockspace_id);
            auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.3f, nullptr, &dockspace_id);
            auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.25f, nullptr, &dockspace_id);

            ImGui::DockBuilderDockWindow("Console", dock_id_down);
            ImGui::DockBuilderDockWindow("Scene", dock_id_left);
            ImGui::DockBuilderDockWindow("Components", dock_id_right);
            ImGui::DockBuilderFinish(dockspace_id);
        }
    }

    ImGui::End();

    draw_entity_picker();

    ImGui::Begin("Console");
    ImGui::Text("LOG");
    ImGui::Text("LOG");
    ImGui::Text("LOG");
    ImGui::End();

    draw_components();
}

void ScenePanel::draw_entity_picker()
{
    ImGui::Begin("Scene");
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    for (size_t entity_id = 0; entity_id < scene().ecs().entity_count(); entity_id++) {
        if (!scene().ecs().has_entity(entity_id)) {
            continue;
        }

        auto tree_node_id = scene().ecs().entity_name(entity_id) + "###" + std::to_string(entity_id);

        if (ImGui::Button(tree_node_id.c_str())) {
            set_focus_on_entity(entity_id);
        }
    }

    ImGui::End();
}

void ScenePanel::draw_components()
{
    ImGui::Begin("Components");

    if (scene().ecs().entity_has_component<TransformComponent>(m_cur_entity)) {
        auto& transform_component = scene().ecs().get_component<TransformComponent>(m_cur_entity);

        if (ImGui::TreeNode("Transform")) {
            ImGui::DragFloat3("Position", (float*)transform_component.position.data(), .1f);
            ImGui::DragFloat3("Rotation", (float*)transform_component.rotation.data(), .1f);
            ImGui::DragFloat3("Scale", (float*)transform_component.scale.data(), .1f);

            ImGui::TreePop();
        }
    }

    if (scene().ecs().entity_has_component<CameraComponent>(m_cur_entity)) {
        auto& camera_component = scene().ecs().get_component<CameraComponent>(m_cur_entity);

        if (ImGui::TreeNode("Camera")) {
            ImGui::DragFloat("Field Of View", &camera_component.field_of_view, .1f);
            ImGui::DragFloat("Near clipping", &camera_component.near_clipping, .1f);
            ImGui::DragFloat("Far clipping", &camera_component.far_clipping, .1f);

            ImGui::TreePop();
        }
    }

    if (scene().ecs().entity_has_component<ModelComponent>(m_cur_entity)) {
        auto& model_component = scene().ecs().get_component<ModelComponent>(m_cur_entity);

        if (ImGui::TreeNode("Model")) {
            memcpy(model_path, model_component.model.mesh().object_path().c_str(), model_component.model.mesh().object_path().size());
            if (ImGui::InputText("Mesh", model_path, sizeof(model_path), ImGuiInputTextFlags_EnterReturnsTrue)) {
                model_component.model.set_mesh(Mesh(model_path));
            }

            if (model_component.model.texture()) {
                memcpy(model_texture_path, model_component.model.texture()->path().c_str(), model_component.model.texture()->path().size());
                if (ImGui::InputText("Texture", model_texture_path, sizeof(model_texture_path), ImGuiInputTextFlags_EnterReturnsTrue)) {
                    model_component.model.set_texture(Constructors::Texture::construct(model_texture_path, Generic::Texture::Types::TEXTURE_2D));
                }
            }

            ImGui::TreePop();
        }
    }

    ImGui::End();
}

void ScenePanel::handle_callback(const ECS::BaseEvent& ecs_event)
{
    if (ecs_event.id() == ECS::EventEnumerator<MouseEntityClickEvent>::ID) {
        ECS::EntityID entity_id = ((const MouseEntityClickEvent&)ecs_event).entity_id;
        set_focus_on_entity(entity_id);
    }
}

void ScenePanel::set_focus_on_entity(ECS::EntityID entity_id)
{
    if (scene().ecs().entity_has_component<FocusableComponent>(m_cur_entity)) {
        auto& focusable_component = scene().ecs().get_component<FocusableComponent>(m_cur_entity);
        focusable_component.focused = false;
    }
    if (scene().ecs().entity_has_component<FocusableComponent>(entity_id)) {
        auto& focusable_component = scene().ecs().get_component<FocusableComponent>(entity_id);
        focusable_component.focused = true;
    }
    m_cur_entity = entity_id;
}