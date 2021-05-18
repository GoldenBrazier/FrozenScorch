#include <GraphicsAPI/Generic/Constructors.h>
#include <GraphicsAPI/Generic/Var.h>
#include <Math/Matrix4f.h>
#include <Math/Numbers.h>
#include <Math/Vector3f.h>
#include <Mesh.h>
#include <Runtime/PNGLoader/PNGLoader.h>
#include <Runtime/Utils/DrawLoop.h>
#include <array>
#include <iostream>
#include <memory>
#include <vector>

int main(int argc, char* argv[])
{
    auto display = Constructors::Display::construct(800, 600, "OpenRenderer");

    std::pair<std::string, int> position = { "position", 0 };

    auto shader = Constructors::Shader::construct(
        std::vector<std::string> { "res/basic_shader.vs", "res/basic_shader.fs" },
        std::vector<std::pair<std::string, int>> { { "position", 0 } },
        std::vector<std::string> { "gScale", "gTranslation", "gRotation" });

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

    auto va = Constructors::VertexArray::construct();
    auto vb = va->construct_vertex_buffer(vertexes.data(), vertexes.size() * sizeof(Math::Vector3f));
    vb->register_attribute_vec3(position.second, false, 0, 0);
    va->construct_index_buffer(indexes.data(), indexes.size());

    auto mesh = Mesh(va);

    // --------------------------------------------

    float rotation = 0;
    float distance = 0;
    float step = 0.05;

    auto raw_img = Runtime::PNGLoader::load<Runtime::ImageType::RGBA>("test.png");
    auto* ddd = raw_img.data<uint32_t*>();

    Runtime::DrawLoop<Runtime::Debug::Off>(60, [&] {
        // TODO: Should move to rendered:
        // display.clear(0, 0.15f, 0.3f, 1.0f);
        glClearColor(0, 0.15f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        shader->bind();
        shader->set_uniform("gScale", 0.55f);
        shader->set_uniform("gTranslation", Math::Matrix4f::Translation({ distance, distance / 2, 0 }));
        shader->set_uniform("gRotation", Math::Matrix4f::RotationAroundZ(rotation));

        mesh.draw();
        display->swap_buffers();

        distance += step;
        if (distance >= 1 || distance <= -1) {
            step *= -1;
        }

        rotation += 0.05f;
        if (rotation > Math::Numbers::pi_v<float> * 2) {
            rotation = 0;
        }

        return display->closed();
    });

    return EXIT_SUCCESS;
}