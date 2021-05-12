#include "Backend/OpenGL/VarTypes.h"
#include "Backend/Var.h"
#include "Display.h"
#include "Mesh.h"
#include "Shader.h"
#include "math/Vector3f.h"
#include <vector>

int main(int argc, char* argv[])
{
    auto display = Display(800, 600, "OpenRenderer");
    auto shader = Backend::Shader({ "res/basic_shader.vs", "res/basic_shader.fs" },
        { Backend::Attribute::construct("position", 0), Backend::Uniform::construct("gScale") });

    auto vertexes = std::vector<Vector3f> { Vector3f(-0.5, -0.5, 0), Vector3f(0, 0.5, 0), Vector3f(0.5, -0.5, 0) };
    auto mesh = Mesh(vertexes);

    //     auto mesh = Mesh({ { -0.5, -0.5, 0 },
    //         { 0, 0.5, 0 },
    //         { 0.5, -0.5, 0 } });

    while (!display.closed()) {
        display.clear(0, 0.15f, 0.3f, 1.0f);
        shader.set_as_primary();
        shader.get_uniform<GL::Float1>("gScale") = 0.55f;
        mesh.draw();
        display.swap_buffers();
    }

    return EXIT_SUCCESS;
}