#include <Application/Application.h>
#include <Application/Events/KeyboardEvent.h>
#include <Editor/Editor.h>
#include <GraphicsAPI/Generic/Constructors.h>
#include <memory>

class EditorApplication : public Application {
public:
    EditorApplication()
        : Application()
    {
        m_editor.init(display(), scene());
    }

    ~EditorApplication() override
    {
        m_editor.shutdown();
    }

    void draw_cycle() override
    {
        m_editor.draw();
    }

    void on_event(const Event& event) override
    {
        if (event.type() == EventType::WindowClose) {
            shutdown();
        }
    }

private:
    Editor m_editor {};
};

int main(int argc, char* argv[])
{
    Ctx.set_grahics_api_type(Generic::GraphicsAPIType::OpenGL);

    EditorApplication editor;
    editor.run();

    return EXIT_SUCCESS;
}