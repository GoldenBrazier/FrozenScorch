#include "Application.h"
#include <Config.h>
#include <GraphicsAPI/Generic/Constructors.h>
#include <GraphicsAPI/Generic/Context.h>
#include <GraphicsAPI/OpenGL/Shader.h>
#include <basic_data.h>
#include <memory>

Application::Application()
{
    m_display = Constructors::Display::construct(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, "OpenRenderer");
    Ctx.set_application(this);

    compile_shaders();
    m_scene.initialize();
}

void Application::run()
{
    if (Ctx.graphics_api_type() == Generic::GraphicsAPIType::Metal) {
        Support::MacOS::Window::Run();
    } else {
        while (m_running) {
            m_scene.update();
            draw_cycle();
            m_display->swap_buffers();
        }
    }
}

void Application::on_event_base(const Event& event)
{
    m_scene.on_event(event);
    on_event(event);
}

void Application::compile_shaders()
{
    // TODO: automate this part
    auto& shader_storage = Ctx.shader_storage();

    std::pair<std::string, int> position = { "position", 0 };
    std::pair<std::string, int> tex_coords = { "tex_coords", 1 };
    std::pair<std::string, int> normal = { "normal", 2 };

    auto uniform_builder = Generic::UniformBuilder();
    uniform_builder.add_var("g_transform", offsetof(BasicShader::Uniforms, scale));
    uniform_builder.add_var("g_perspective", offsetof(BasicShader::Uniforms, perspective));
    uniform_builder.add_var("g_viewMatrix", offsetof(BasicShader::Uniforms, view_matrix));
    uniform_builder.add_var("g_ambient_brightness", offsetof(BasicShader::Uniforms, ambient_brightness));
    uniform_builder.add_var("g_camera_position", offsetof(BasicShader::Uniforms, camera_position));
    uniform_builder.add_array<NR_POINT_LIGHTS, sizeof(Math::Vector3f)>("g_light_position", offsetof(BasicShader::Uniforms, light_position));
    uniform_builder.add_array<NR_POINT_LIGHTS, sizeof(Math::Vector3f)>("g_light_color", offsetof(BasicShader::Uniforms, light_color));
    uniform_builder.add_array<NR_POINT_LIGHTS, sizeof(Math::Vector3f)>("g_light_attenuation", offsetof(BasicShader::Uniforms, light_attenuation));

    std::shared_ptr<Generic::Shader> basic_shader;
    std::shared_ptr<Generic::Shader> mapper2d_shader;

    if (Ctx.graphics_api_type() == Generic::GraphicsAPIType::Metal) {
        basic_shader = Constructors::Shader::construct(
            "res/basic.metal",
            "vert_func",
            "frag_func",
            uniform_builder.data(),
            sizeof(BasicShader::Uniforms));
    } else {
        basic_shader = Constructors::Shader::construct(std::vector<std::string> { "res/basic_shader.vs", "res/basic_shader.fs" });
        mapper2d_shader = Constructors::Shader::construct(std::vector<std::string> { "res/mapper2d_shader.vs", "res/mapper2d_shader.fs" });
    }

    shader_storage.add("basic_shader", basic_shader);
    shader_storage.add("mapper2d_shader", mapper2d_shader);
}
