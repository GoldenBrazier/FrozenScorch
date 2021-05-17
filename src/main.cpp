#include <Backend/OpenGL/VarTypes.h>
#include <Backend/Var.h>
#include <Display.h>
#include <Math/Matrix4f.h>
#include <Math/Numbers.h>
#include <Math/Vector3f.h>
#include <Mesh.h>
#include <Runtime/PNGLoader/PNGLoader.h>
#include <Runtime/Utils/DrawLoop.h>
#include <Shader.h>
#include <iostream>
#include <Shader.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <array>
#include <iostream>
#include <memory>
#include <vector>

int main(int argc, char* argv[])
{
    auto display = Display(800, 600, "OpenRenderer");

    auto position = Backend::Attribute::construct("position", 0, 3);

    auto shader = Backend::Shader({ "res/basic_shader.vs", "res/basic_shader.fs" },
        { position, Backend::Uniform::construct("gScale"),
            Backend::Uniform::construct("gTranslation"), Backend::Uniform::construct("gRotation") });

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

    auto va = VertexArray::construct();
    auto vb = va->construct_vertex_buffer(vertexes.data(), vertexes.size() * sizeof(Math::Vector3f));
    
    vb->register_attribute<GL::Vec3>(position, false, 0, 0);
    va->set_index_buffer(IndexBuffer::construct(indexes.data(), indexes.size()));

    auto mesh = Mesh(va);

    // --------------------------------------------
    
    float rotation = 0;
    float distance = 0;
    float step = 0.05;

    auto raw_img = Runtime::PNGLoader::load<Runtime::ImageType::RGBA>("test.png");
    auto* ddd = raw_img.data<uint32_t*>();

    Runtime::DrawLoop<Runtime::Debug::Off>(60, [&] {
        display.clear(0, 0.15f, 0.3f, 1.0f);

        shader.set_as_primary();
        shader.get_uniform<GL::Float>("gScale") = 0.55f;
        shader.get_uniform<GL::Mat4>("gTranslation") = Math::Matrix4f::Translation({ distance, distance / 2, 0 });
        shader.get_uniform<GL::Mat4>("gRotation") = Math::Matrix4f::RotationAroundZ(rotation);

        mesh.draw();
        display.swap_buffers();

        distance += step;
        if (distance >= 1 || distance <= -1) {
            step *= -1;
        }

        rotation += 0.05f;
        if (rotation > Math::Numbers::pi_v<float> * 2) {
            rotation = 0;
        }

        return display.closed();
    });

    return EXIT_SUCCESS;
}