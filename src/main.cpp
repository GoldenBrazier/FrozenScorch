#include <Application/Application.h>
#include <Application/Camera.h>
#include <Application/Events/KeyboardEvent.h>
#include <Application/Events/MouseEvent.h>
#include <Application/KeyCodes.h>
#include <GraphicsAPI/Generic/Constructors.h>
#include <GraphicsAPI/Generic/Var.h>
#include <GraphicsAPI/Generic/Vertex.h>
#include <Math/Matrix4f.h>
#include <Math/Numbers.h>
#include <Math/Vector3f.h>
#include <Mesh.h>
#include <Parsers/ObjParser.h>
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

class ExampleApplication : public Application {
public:
    ExampleApplication()
        : Application()
    {
        renderer = Constructors::Renderer::construct();

        std::pair<std::string, int> position = { "position", 0 };
        std::pair<std::string, int> tex_coords = { "tex_coords", 1 };
        std::pair<std::string, int> normal = { "normal", 2 };

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
                    { "g_viewMatrix", offsetof(BasicShader::Uniforms, view_matrix) },
                },
                sizeof(BasicShader::Uniforms));
        } else {
            shader = Constructors::Shader::construct(
                std::vector<std::string> { "res/basic_shader.vs", "res/basic_shader.fs" },
                std::vector<std::pair<std::string, int>> { position, tex_coords, normal },
                std::vector<std::string> {
                    "g_sampler", "g_scale", "g_translation", "g_rotation",
                    "g_perspective", "g_viewMatrix", "g_ambient_brightness",
                    "g_light_position", "g_light_color", "g_camera_position" });
        }

        // ---------- initail data to render ----------

        auto parser = ObjParser("res/models/water_tower/water_tower.obj");
        parser.parse();

        texture = Constructors::Texture::construct(Runtime::PNGLoader::load_rgba("res/models/water_tower/water_tower.png"), Generic::Texture::Types::TEXTURE_2D);

        vertex_array = Constructors::VertexArray::construct();
        auto vb = vertex_array->construct_vertex_buffer(parser.vertexes().data(), parser.vertexes().size() * sizeof(Generic::Vertex));

        vb->register_attribute_vec3(position.second, sizeof(Generic::Vertex), 0);
        vb->register_attribute_vec2(tex_coords.second, sizeof(Generic::Vertex), sizeof(Math::Vector3f));
        vb->register_attribute_vec3(normal.second, sizeof(Generic::Vertex), sizeof(Math::Vector3f) + sizeof(Math::Vector2f));
        vertex_array->construct_index_buffer(parser.indeces().data(), parser.indeces().size());
    }

    void draw_cycle() override
    {
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

        renderer->begin();
        renderer->clear();

        texture->bind(0);
        shader->bind();
        shader->set_uniform("g_sampler", (int)0);
        shader->set_uniform("g_light_color", Math::Vector3f(1, 1, 1));
        shader->set_uniform("g_scale", 1.0f);
        shader->set_uniform("g_translation", Math::Matrix4f::Translation({ distance, distance / 2, 0 }));
        shader->set_uniform("g_rotation", Math::Matrix4f::RotationAroundZ(rotation));
        shader->set_uniform("g_perspective", Math::Matrix4f::Perspective(800, 600, 0.01f, 1000.0f, 90));
        shader->set_uniform("g_viewMatrix", m_camera.view_matrix());
        shader->set_uniform("g_ambient_brightness", 0.3f);
        shader->set_uniform("g_light_position", m_camera.position());
        shader->set_uniform("g_camera_position", m_camera.position());

        renderer->draw_indexed(vertex_array);
        renderer->end();

//        distance += step;
//        if (distance >= 1 || distance <= -1) {
//            step *= -1;
//        }
//
//        rotation += 0.05f;
//        if (rotation > Math::Numbers::pi_v<float> * 2) {
//            rotation = 0;
//        }
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
            std::cout << mouse_event.x() << " " << mouse_event.y() << "\n";

            float horizontal_turn = -3.14f * mouse_event.x() / 800;
            float vertical_turn = -3.14f * mouse_event.y() / 600;

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

    bool w;
    bool a;
    bool s;
    bool d;

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