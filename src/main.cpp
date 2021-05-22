#include <Application/Application.h>
#include <GraphicsAPI/Generic/Constructors.h>
#include <GraphicsAPI/Generic/Var.h>
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

class ExampleApplication : public Application {
public:
    ExampleApplication()
        : Application()
    {
        renderer = Constructors::Renderer::construct();

        std::pair<std::string, int> position = { "position", 0 };

        if (Ctx.graphics_api_type() == Generic::GraphicsAPIType::Metal) {
            shader = Constructors::Shader::construct(
                "res/basic.metal",
                "vert_func",
                "frag_func",
                std::vector<std::pair<std::string, int>> {
                    { "gScale", offsetof(BasicShader::Uniforms, scale) },
                    { "gRotation", offsetof(BasicShader::Uniforms, rot) },
                    { "gTranslation", offsetof(BasicShader::Uniforms, trans) },
                    { "gPerspective", offsetof(BasicShader::Uniforms, perspective) },
                },
                sizeof(BasicShader::Uniforms));
        } else {
            shader = Constructors::Shader::construct(
                std::vector<std::string> { "res/basic_shader.vs", "res/basic_shader.fs" },
                std::vector<std::pair<std::string, int>> { { "position", 0 } },
                std::vector<std::string> { "gScale", "gTranslation", "gRotation", "gPerspective" });
        }

        // ---------- initail data to render ----------

        auto vertexes = std::array<Math::Vector3f, 4> {
            Math::Vector3f(-0.5, -0.5, 4),
            Math::Vector3f(0.5, -0.5, 4),
            Math::Vector3f(0.5, 0.5, 4),
            Math::Vector3f(-0.5, 0.5, 4),
        };

        // clang-format off
        auto indexes = std::array<uint32_t, 6> {
            0, 1, 2,
            2, 3, 0,
        };

        vertex_array = Constructors::VertexArray::construct();
        auto vb = vertex_array->construct_vertex_buffer(vertexes.data(), vertexes.size() * sizeof(Math::Vector3f));
        vb->register_attribute_vec3(position.second, 0, 0);
        vertex_array->construct_index_buffer(indexes.data(), indexes.size());
    }

    void draw_cycle() override
    {
        renderer->set_clear_color(0, 0.15f, 0.3f, 1.0f);

        renderer->begin();
        renderer->clear();

        shader->bind();
        shader->set_uniform("gScale", 0.55f);
        shader->set_uniform("gTranslation", Math::Matrix4f::Translation({ distance, distance / 2, 0 }));
        shader->set_uniform("gRotation", Math::Matrix4f::RotationAroundZ(rotation));
        shader->set_uniform("gPerspective", Math::Matrix4f::Perspective(800, 600, 1, 6, 90));

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
        if (event.type() == EventType::WindowClose) {
            shutdown();
        }
        std::cout << "application recieved an event\n";
    }

private:
    std::shared_ptr<Generic::Shader> shader;
    std::shared_ptr<Generic::Display> display;
    std::shared_ptr<Generic::Renderer> renderer;
    std::shared_ptr<Generic::VertexArray> vertex_array;

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