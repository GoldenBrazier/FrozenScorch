#include <Application/Application.h>
#include <Application/Camera.h>
#include <Application/Events/KeyboardEvent.h>
#include <Application/Events/MouseEvent.h>
#include <Application/KeyCodes.h>
#include <GraphicsAPI/Generic/Constructors.h>
#include <Math/Matrix4f.h>
#include <Math/Numbers.h>
#include <Model.h>
#include <Renderer/Renderer.h>
#include <memory>
#include <vector>

#include <ECS/ECS.h>

static constexpr size_t ComponentCount = 32;
static constexpr size_t SystemCount = 8;

struct Position : public Component<Position> {
    float x {};
    float y {};
};

class MoveSystem : public System<ComponentCount, SystemCount> {
public:
    explicit MoveSystem(ECS<ComponentCount, SystemCount>* ecs)
        : System<ComponentCount, SystemCount>(ecs)
    {
        set_required_components<Position>();
    }

    void update()
    {
        for (auto& entity : m_managed_entities) {
            auto& position = ecs().get_component<Position>(entity);
            position.x += 10;
            position.y += 10;

            std::cout << position.x << " " << position.y << std::endl;
        }
    }
};

class ExampleApplication : public Application {
public:
    ExampleApplication()
        : Application()
    {
        renderer = Constructors::Renderer::construct();

        m_shader = Ctx.shader_storage().get("basic_shader");

        m_models.emplace_back("water_tower");
        m_models.emplace_back("crate");
        m_models.emplace_back("water_tower");
        m_models.emplace_back("crate");

        float distance = 0;

        for (int i = 0; i < m_models.size(); i++) {
            auto translation = Math::Matrix4f::Translation({ distance, 0, 0 });
            auto rotation = Math::Matrix4f::RotationAroundZ(0);
            auto scale = Math::Matrix4f::Scaling(1);

            m_models_transforms.emplace_back(translation * rotation * scale);

            distance += 10;
        }

        // ECS
        ecs.register_component<Position>();
        m_move_system = ecs.create_system<MoveSystem>();

        auto entity_id = ecs.create_entity();
        ecs.add_component<Position>(entity_id);
    }

    void draw_cycle() override
    {
        m_move_system->update();

        if (w) {
            m_camera.move_forward();
        }
        if (a) {
            m_camera.move_left();
        }
        if (s) {
            m_camera.move_backward();
        }
        if (d) {
            m_camera.move_right();
        }

        renderer->set_clear_color(0, 0.15f, 0.3f, 1.0f);

        renderer->begin_scene(m_camera);
        renderer->clear();

        int transform_at = 0;

        for (const auto& model : m_models) {
            renderer->draw_model(model, m_shader, m_models_transforms[transform_at++]);
        }

        renderer->end_scene();
    }

    void on_event(const Event& event) override
    {
        if (event.type() == EventType::WindowClose) {
            shutdown();
        }

        if (event.type() == EventType::KeyboardPressed) {
            auto& keyboard_event = (KeyboardPressedEvent&)(event);
            if (keyboard_event.key() == OpenRenderer::KEYCODE_W) {
                w = true;
            }
            if (keyboard_event.key() == OpenRenderer::KEYCODE_S) {
                s = true;
            }
            if (keyboard_event.key() == OpenRenderer::KEYCODE_A) {
                a = true;
            }
            if (keyboard_event.key() == OpenRenderer::KEYCODE_D) {
                d = true;
            }
        }

        if (event.type() == EventType::KeyboardReleased) {
            auto& keyboard_event = (KeyboardPressedEvent&)(event);
            if (keyboard_event.key() == OpenRenderer::KEYCODE_W) {
                w = false;
            }
            if (keyboard_event.key() == OpenRenderer::KEYCODE_S) {
                s = false;
            }
            if (keyboard_event.key() == OpenRenderer::KEYCODE_A) {
                a = false;
            }
            if (keyboard_event.key() == OpenRenderer::KEYCODE_D) {
                d = false;
            }
        }

        if (event.type() == EventType::MouseMove) {
            auto& mouse_event = (MouseMoveEvent&)(event);

            float horizontal_turn = -Math::Numbers::pi_v<float> * mouse_event.x() / 800;
            float vertical_turn = -Math::Numbers::pi_v<float> * mouse_event.y() / 600;

            m_camera.turn_horizontally(horizontal_turn);
            m_camera.turn_vertically(vertical_turn);
        }
    }

private:
    std::shared_ptr<Generic::Renderer> renderer;

    Camera m_camera { Camera({ 0, 0, 0 }, { 0, 1, 0 }) };

    std::shared_ptr<Generic::Shader> m_shader;
    std::vector<Model> m_models;

    // For now, we store transforms for each model in a vector because Model shouldn't contain such information.
    // In the feature, there will be a transform component for an entity.
    std::vector<Math::Matrix4f> m_models_transforms;

    bool w {};
    bool a {};
    bool s {};
    bool d {};

    // ECS
    ECS<ComponentCount, SystemCount> ecs;
    MoveSystem* m_move_system;
};

int main(int argc, char* argv[])
{
    Ctx.set_grahics_api_type(Generic::GraphicsAPIType::OpenGL);

    ExampleApplication example;
    example.run();

    return EXIT_SUCCESS;
}