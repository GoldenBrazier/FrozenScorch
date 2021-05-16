#include <Backend/Metal/Display.h>
#include <Backend/OpenGL/VarTypes.h>
#include <Backend/Var.h>
#include <Display.h>
#include <Math/Matrix4f.h>
#include <Math/Numbers.h>
#include <Math/Vector3f.h>
#include <Mesh.h>
#include <Runtime/MacOS/Window.h>
#include <Runtime/PNGLoader/PNGLoader.h>
#include <Runtime/Utils/DrawLoop.h>
#include <Runtime/Utils/FS.h>
#include <Shader.h>
#include <iostream>
#include <shaders/Metal/ShaderData.h>
#include <vector>

MTL::CommandQueue cmd_queue;
MTL::Buffer vertex_buffer;
MTL::Buffer vertex_uniform;
MTL::Buffer frag_buffer;
MTL::RenderPipelineState render_pipeline_state;

float rotation = 0;
float distance = 0;
float step = 0.01;

void Render(const Runtime::MacOS::Window& win)
{
    auto cmd_buffer = cmd_queue.CommandBuffer();
    auto renderpass_descriptor = win.renderpass_descriptor();
    renderpass_descriptor.GetColorAttachments()[0].SetClearColor({ 0, 0.15f, 0.3f, 1.0f });

    if (renderpass_descriptor) {
        auto rc_encoder = cmd_buffer.RenderCommandEncoder(renderpass_descriptor);
        rc_encoder.SetRenderPipelineState(render_pipeline_state);
        rc_encoder.SetVertexBuffer(vertex_buffer, 0, 0);
        rc_encoder.SetVertexBuffer(vertex_uniform, 0, 1);
        rc_encoder.SetFragmentBuffer(frag_buffer, 0, 0);
        rc_encoder.Draw(MTL::PrimitiveType::Triangle, 0, 3);
        rc_encoder.EndEncoding();
        cmd_buffer.Present(win.drawable());
    }

    cmd_buffer.Commit();
    cmd_buffer.WaitUntilCompleted();

    distance += step;
    if (distance >= 1 || distance <= -1) {
        step *= -1;
    }

    rotation += 0.05f;
    if (rotation > Math::Numbers::pi_v<float> * 2) {
        rotation = 0;
    }

    VertUniforms* x = (VertUniforms*)vertex_uniform.GetContents();
    memcpy(&x->trans, Math::Matrix4f::Translation({ distance, distance/2, 0 }).data(), sizeof(x->trans));
    memcpy(&x->rot, Math::Matrix4f::RotationAroundZ(rotation).data(), sizeof(x->rot));
}

int main(int argc, char* argv[])
{
    std::vector<Math::Vector3f> vertexes = { Math::Vector3f(-0.5, -0.5, 0), Math::Vector3f(0, 0.5, 0), Math::Vector3f(0.5, -0.5, 0) };
#ifdef IGNORE
    auto display = Display(800, 600, "OpenRenderer");
    auto shader = Backend::Shader({ "res/basic_shader.vs", "res/basic_shader.fs" },
        { Backend::Attribute::construct("position", 0), Backend::Uniform::construct("gScale"),
            Backend::Uniform::construct("gTranslation"), Backend::Uniform::construct("gRotation") });

    auto mesh = Mesh(vertexes);

    auto raw_img = Runtime::PNGLoader::load<Runtime::ImageType::RGBA>("test.png");
    auto* ddd = raw_img.data<uint32_t*>();

    Runtime::DrawLoop<Runtime::Debug::Off>(60, [&] {
        display.clear(0, 0.15f, 0.3f, 1.0f);

        shader.set_as_primary();
        shader.get_uniform<GL::Float>("gScale") = 1.0f;
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
#else

    auto metal_shader = Runtime::FS::load_shader("res/shaders/Metal/basic.metal");

    FragmentUniforms frags = { 0.55f };
    VertUniforms verts = {};
    memcpy(&verts, Math::Matrix4f::Translation({ distance, distance / 2, 0 }).data(), sizeof(verts));

    auto display = Metal::Display(800, 600, &Render);
    cmd_queue = display.device().NewCommandQueue();

    ns::Error error_buffer;
    MTL::Library library = display.device().NewLibrary(metal_shader.c_str(), MTL::CompileOptions(), &error_buffer);
    if (!library.GetPtr()) {
        std::cout << error_buffer.GetLocalizedDescription().GetCStr() << std::endl;
        return 0;
    }
    MTL::Function vert_func = library.NewFunction("vert_func");
    MTL::Function frag_func = library.NewFunction("frag_func");

    vertex_buffer = display.device().NewBuffer(vertexes.data(), vertexes.size() * sizeof(float) * 3, MTL::ResourceOptions::CpuCacheModeDefaultCache);
    vertex_uniform = display.device().NewBuffer(&verts, sizeof(verts), MTL::ResourceOptions::CpuCacheModeDefaultCache);
    frag_buffer = display.device().NewBuffer(&frags, sizeof(frags), MTL::ResourceOptions::CpuCacheModeDefaultCache);

    // Mapping:
    FragmentUniforms* x = (FragmentUniforms*)frag_buffer.GetContents();
    x->brightness = 1.0f;

    MTL::RenderPipelineDescriptor render_pipeline_desc;
    render_pipeline_desc.SetVertexFunction(vert_func);
    render_pipeline_desc.SetFragmentFunction(frag_func);
    render_pipeline_desc.GetColorAttachments()[0].SetPixelFormat(MTL::PixelFormat::BGRA8Unorm);
    render_pipeline_state = display.device().NewRenderPipelineState(render_pipeline_desc, nullptr);

    display.run();

#endif
    return EXIT_SUCCESS;
}