#include <Application/Application.h>
#include <Application/Camera.h>
#include <GraphicsAPI/Generic/Constructors.h>
#include <GraphicsAPI/Generic/Var.h>
#include <GraphicsAPI/Generic/Vertex.h>
#include <Math/Matrix4f.h>
#include <Math/Numbers.h>
#include <Math/Vector3f.h>
#include <Mesh.h>
#include <Renderer/Renderer.h>
#include <Runtime/PNGLoader/PNGLoader.h>
#include <Runtime/Utils/DrawLoop.h>
#include <Runtime/Utils/SizeOfData.h>
#include <Support/MacOS/Window.h>
#include <array>
#include <basic_data.h>
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>
#include <Application/Events/KeyboardEvent.h>
#include <Application/Events/MouseEvent.h>
#include <Application/KeyCodes.h>

class ExampleApplication : public Application {
public:
    ExampleApplication()
        : Application()
    {
        renderer = Constructors::Renderer::construct();

        std::pair<std::string, int> position = { "position", 0 };
        std::pair<std::string, int> tex_coords = { "tex_coords", 1 };

        if (Ctx.graphics_api_type() == Generic::GraphicsAPIType::Metal) {
            shader = Constructors::Shader::construct(
                "res/basic.metal",
                "vert_func",
                "frag_func",
                std::vector<std::pair<std::string, int>> {
                    { "g_scale", offsetof(BasicShader::Uniforms, scale) },
                    { "g_rotation", offsetof(BasicShader::Uniforms, rot) },
                    { "g_translation", offsetof(BasicShader::Uniforms, trans) },
                    { "g_perspective", offsetof(BasicShader::Uniforms, perspective) },
                },
                sizeof(BasicShader::Uniforms));
        } else {
            shader = Constructors::Shader::construct(
                std::vector<std::string> { "res/basic_shader.vs", "res/basic_shader.fs" },
                std::vector<std::pair<std::string, int>> { position, tex_coords },
                std::vector<std::string> { "g_sampler", "g_scale", "g_translation", "g_rotation", "g_perspective", "g_viewMatrix" });
        }

        // ---------- initail data to render ----------

        auto vertexes = std::array<Generic::Vertex, 4> {
            Generic::Vertex { Math::Vector3f(-0.5, -0.5, 2), Math::Vector2f(-0.5, -0.5) },
            Generic::Vertex { Math::Vector3f(0.5, -0.5, 2), Math::Vector2f(0.5, -0.5) },
            Generic::Vertex { Math::Vector3f(0.5, 0.5, 2), Math::Vector2f(0.5, 0.5) },
            Generic::Vertex { Math::Vector3f(-0.5, 0.5, 2), Math::Vector2f(-0.5, 0.5) },
        };

        // clang-format off
        auto indexes = std::array<uint32_t, 6> {
            0, 1, 2,
            2, 3, 0,
        };
        // clang-format on

        texture = Constructors::Texture::construct(Runtime::PNGLoader::load_rgba("res/texture.png"), Generic::Texture::Types::TEXTURE_2D);

        vertex_array = Constructors::VertexArray::construct();
        auto vb = vertex_array->construct_vertex_buffer(vertexes.data(), vertexes.size() * sizeof(Generic::Vertex));
        vb->register_attribute_vec3(position.second, sizeof(Generic::Vertex), 0);
        vb->register_attribute_vec2(tex_coords.second, sizeof(Generic::Vertex), sizeof(Math::Vector3f));
        vertex_array->construct_index_buffer(indexes.data(), indexes.size());
    }

    void draw_cycle() override
    {
        renderer->set_clear_color(0, 0.15f, 0.3f, 1.0f);

        renderer->begin();
        renderer->clear();

        texture->bind(0);
        shader->bind();
        shader->set_uniform("g_sampler", (int)0);
        shader->set_uniform("g_scale", 1.0f);
        shader->set_uniform("g_translation", Math::Matrix4f::Translation({ distance, distance / 2, 0 }));
        shader->set_uniform("g_rotation", Math::Matrix4f::RotationAroundZ(rotation));
        shader->set_uniform("g_perspective", Math::Matrix4f::Perspective(800, 600, 1, 6, 90));
        shader->set_uniform("g_viewMatrix", m_camera.view_matrix());

        renderer->draw_indexed(vertex_array);
        renderer->end();

        distance += step;
        if (distance >= 1 || distance <= -1) {
            step *= -1;
        }

        rotation += 0.05f;
        if (rotation > Math::Numbers::pi_v<float> * 2) {
            rotation = 0;
        }
    }

    void on_event(const Event& event) override
    {
        // Camera camera({ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 });
        if (event.type() == EventType::WindowClose) {
            shutdown();
        }

        if (event.type() == EventType::KeyboardPressed) {
            auto& keyboard_event = (KeyboardPressedEvent&)(event);
            if (keyboard_event.key() == OpenRenderer::KEYCODE_W) {
                m_camera.move_forward();
            }
            if (keyboard_event.key() == OpenRenderer::KEYCODE_S) {
                m_camera.move_backward();
            }
            if (keyboard_event.key() == OpenRenderer::KEYCODE_A) {
                m_camera.move_left();
            }
            if (keyboard_event.key() == OpenRenderer::KEYCODE_D) {
                m_camera.move_right();
            }
        }

        if (event.type() == EventType::MouseMove) {
            auto& mouse_event = (MouseMoveEvent&)(event);
            std::cout << mouse_event.x() << " " << mouse_event.y() << "\n";

            if(!mouse_ready) {
                last_x = mouse_event.x();
                last_y = mouse_event.y();
                mouse_ready = true;
                return;
            }

            int dist_x = last_x - mouse_event.x();
            int dist_y = last_y - mouse_event.y();

            last_x = mouse_event.x();
            last_y = mouse_event.y();

            float horizontal_turn = 3.14f * dist_x / 800;
            float vertical_turn = 3.14f * dist_y / 800;

            m_camera.turn_horizontally(horizontal_turn);
            m_camera.turn_vertically(vertical_turn);
        }
    }

private:
    Camera m_camera { Camera({ 0, 0, 0 }, { 0, 1, 0 }) };

    std::shared_ptr<Generic::Shader> shader;
    std::shared_ptr<Generic::Display> display;
    std::shared_ptr<Generic::Renderer> renderer;
    std::shared_ptr<Generic::VertexArray> vertex_array;
    std::shared_ptr<Generic::Texture> texture;

    int last_x {};
    int last_y {};
    bool mouse_ready {};

    float rotation = 0;
    float distance = 0;
    float step = 0.05;
};

int main(int argc, char* argv[])
{
    Ctx.set_grahics_api_type(Generic::GraphicsAPIType::OpenGL);

    ExampleApplication example;
    example.run();

    return EXIT_SUCCESS;
}