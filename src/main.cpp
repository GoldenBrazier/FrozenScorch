#include "Display.h"
#include "Shader.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "Mesh.h"
#include "math/Vector3f.h"

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[])
{
    auto a = 333;
    std::cout << a;
    
    auto display = Display(800, 600, "OpenRenderer");
    auto shader = Shader("res/basic_shader");

    auto vertexes = std::vector<Vector3f>{Vector3f(-0.5, -0.5, 0), Vector3f(0, 0.5, 0), Vector3f(0.5, -0.5, 0)};
    // auto mesh = Mesh(vertexes);

    // auto mesh = Mesh({ { -0.5, -0.5, 0 },
    //     { 0, 0.5, 0 },
    //     { 0.5, -0.5, 0 } });

    while (!display.closed()) {
        display.clear(0, 0.15f, 0.3f, 1.0f);
        shader.bind();
        // mesh.draw();
        display.swap_buffers();
    }

    return EXIT_SUCCESS;
}