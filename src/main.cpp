#include <Application/Application.h>
#include <Application/Events/KeyboardEvent.h>
#include <GraphicsAPI/Generic/Constructors.h>
#include <Renderer/Renderer.h>
#include <memory>

class ExampleApplication : public Application {
public:
    void draw_cycle() override
    {
        std::cout << "drawing callback!" << std::endl;
    }

    void on_event(const Event& event) override
    {
        std::cout << "event callback!" << std::endl;

        if (event.type() == EventType::WindowClose) {
            shutdown();
        }
    }
};

int main(int argc, char* argv[])
{
    Ctx.set_grahics_api_type(Generic::GraphicsAPIType::OpenGL);

    ExampleApplication example;
    example.run();

    return EXIT_SUCCESS;
}