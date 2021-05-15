#include <Backend/OpenGL/VarTypes.h>
#include <Backend/Var.h>
#include <Display.h>
#include <Math/Matrix4f.h>
#include <Math/Numbers.h>
#include <Math/Vector3f.h>
#include <Mesh.h>
#include <Runtime/PNGLoader/PNGLoader.h>
#include <Shader.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    auto display = Display(800, 600, "OpenRenderer");
    auto shader = Backend::Shader({ "res/basic_shader.vs", "res/basic_shader.fs" },
        { Backend::Attribute::construct("position", 0), Backend::Uniform::construct("gScale"),
            Backend::Uniform::construct("gTranslation"), Backend::Uniform::construct("gRotation") });

    auto vertexes = std::vector<Math::Vector3f> { Math::Vector3f(-0.5, -0.5, 0), Math::Vector3f(0, 0.5, 0), Math::Vector3f(0.5, -0.5, 0) };
    auto mesh = Mesh(vertexes);

    float rotation = 0;
    float distance = 0;
    float step = 0.05;

    auto raw_img = Runtime::PNGLoader::load<Runtime::ImageType::RGBA>("test.png");
    auto* ddd = raw_img.data<uint32_t*>();

    while (!display.closed()) {
        display.clear(0, 0.15f, 0.3f, 1.0f);

        shader.set_as_primary();
        shader.get_uniform<GL::Float1>("gScale") = 0.55f;
        shader.get_uniform<GL::Matrix4v>("gTranslation") = Math::Matrix4f::Translation({ distance, distance / 2, 0 });
        shader.get_uniform<GL::Matrix4v>("gRotation") = Math::Matrix4f::RotationAroundZ(rotation);

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
    }

    return EXIT_SUCCESS;
}