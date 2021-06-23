#pragma once

#include <Application/Application.h>
#include <Math/Matrix4f.h>
#include <Math/Numbers.h>
#include <Model.h>
#include <Renderer/Renderer.h>
#include <memory>
#include <utility>
#include <vector>

#include <ECS/ECS.h>
#include <Config.h>

class RenderSystem : public System<Config::ComponentCount, Config::SystemCount> {
public:
    explicit RenderSystem(ECS<Config::ComponentCount, Config::SystemCount>* ecs, std::shared_ptr<Generic::Renderer> renderer, const Camera& camera)
        : System<Config::ComponentCount, Config::SystemCount>(ecs)
        , renderer(std::move(renderer))
        , camera(camera)
    {
        set_required_components<TransformComponent, ModelComponent, ShaderComponent>();
    }

    void update() override
    {
        renderer->set_clear_color(0, 0.15f, 0.3f, 1.0f);
        renderer->begin_scene(camera);
        renderer->clear();

        for (auto entity_id : m_managed_entities) {
            auto& model = ecs().get_component<ModelComponent>(entity_id).model;
            auto& shader = ecs().get_component<ShaderComponent>(entity_id).shader;
            auto& transform = ecs().get_component<TransformComponent>(entity_id).transform();

            renderer->draw_model(model, shader, transform);
        }

        renderer->end_scene();
    }

private:
    std::shared_ptr<Generic::Renderer> renderer;
    const Camera& camera;
};