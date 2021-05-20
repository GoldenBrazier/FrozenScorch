#include <GraphicsAPI/Generic/Constructors.h>
#include <GraphicsAPI/Generic/Var.h>
#include <Math/Matrix4f.h>
#include <Math/Numbers.h>
#include <Math/Vector3f.h>
#include <Mesh.h>
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
#include <Renderer/Renderer.h>

float rotation = 0;
float distance = 0;
float step = 0.05;
std::shared_ptr<Generic::Shader> shader;
std::shared_ptr<Generic::Display> display;
std::shared_ptr<Generic::Renderer> renderer;
std::shared_ptr<Generic::VertexArray> vertex_array;

void main_loop_callback()
{
    renderer->set_clear_color(0, 0.15f, 0.3f, 1.0f);

    renderer->begin();
        renderer->clear();

        shader->bind();
        shader->set_uniform("gScale", 0.55f);
        shader->set_uniform("gTranslation", Math::Matrix4f::Translation({ distance, distance / 2, 0 }));
        shader->set_uniform("gRotation", Math::Matrix4f::RotationAroundZ(rotation));

        renderer->draw_indexed(vertex_array);
    renderer->end();

    display->swap_buffers();

    if (display->closed()) {
        std::abort();
    }

    distance += step;
    if (distance >= 1 || distance <= -1) {
        step *= -1;
    }

    rotation += 0.05f;
    if (rotation > Math::Numbers::pi_v<float> * 2) {
        rotation = 0;
    }
}

int main(int argc, char* argv[])
{
    display = Constructors::Display::construct(800, 600, "OpenRenderer");
    renderer = Constructors::Renderer::construct();

    std::pair<std::string, int> position = { "position", 0 };

    if (false) {
        shader = Constructors::Shader::construct(
            "res/basic.metal",
            "vert_func",
            "frag_func",
            std::vector<std::pair<std::string, int>> {
                { "gScale", offsetof(BasicShader::Uniforms, scale) },
                { "gRotation", offsetof(BasicShader::Uniforms, rot) },
                { "gTranslation", offsetof(BasicShader::Uniforms, trans) },
            },
            sizeof(BasicShader::Uniforms));
    } else {
        shader = Constructors::Shader::construct(
            std::vector<std::string> { "res/basic_shader.vs", "res/basic_shader.fs" },
            std::vector<std::pair<std::string, int>> { { "position", 0 } },
            std::vector<std::string> { "gScale", "gTranslation", "gRotation" });
    }

    // ---------- initail data to render ----------

    auto vertexes = std::array<Math::Vector3f, 4> {
        Math::Vector3f(-0.5, -0.5, 0),
        Math::Vector3f(0.5, -0.5, 0),
        Math::Vector3f(0.5, 0.5, 0),
        Math::Vector3f(-0.5, 0.5, 0),
    };

    auto indexes = std::array<uint32_t, 6> {
        0, 1, 2,
        2, 3, 0,
    };

    auto main_loop = Constructors::MainLoop::construct(main_loop_callback);

    vertex_array = Constructors::VertexArray::construct();
    auto vb = vertex_array->construct_vertex_buffer(vertexes.data(), vertexes.size() * sizeof(Math::Vector3f));
    vb->register_attribute_vec3(position.second, 0, 0);
    vertex_array->construct_index_buffer(indexes.data(), indexes.size());

    // --------------------------------------------
    main_loop->run();
    return EXIT_SUCCESS;
}