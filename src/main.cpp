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

float rotation = 0;
float distance = 0;
float step = 0.05;
std::shared_ptr<Generic::Shader> shader;
std::shared_ptr<Generic::Display> display;

// TODO: Should be removed
MTL::Buffer vertex_buffer;
MTL::Buffer index_buffer;

void main_loop_callback()
{
    // TODO: Should move to Renderer:
    // display.clear(0, 0.15f, 0.3f, 1.0f);

#ifndef METAL
    glClearColor(0, 0.15f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
#else
    auto cmd_buffer = Ctx.metal_context()->cmd_queue().CommandBuffer();
    auto renderpass_descriptor = Ctx.metal_context()->window().renderpass_descriptor();
    if (!renderpass_descriptor) {
        return;
    }
    renderpass_descriptor.GetColorAttachments()[0].SetClearColor({ 0, 0.15f, 0.3f, 1.0f });
    auto rc_encoder = cmd_buffer.RenderCommandEncoder(renderpass_descriptor);
    Ctx.metal_context()->set_render_encoder(&rc_encoder);
#endif

    shader->bind();
    shader->set_uniform("gScale", 0.55f);
    shader->set_uniform("gTranslation", Math::Matrix4f::Translation({ distance, distance / 2, 0 }));
    shader->set_uniform("gRotation", Math::Matrix4f::RotationAroundZ(rotation));

#ifndef METAL
    mesh.draw();
#else
    rc_encoder.SetVertexBuffer(vertex_buffer, 0, 0);
    rc_encoder.DrawIndexed(MTL::PrimitiveType::Triangle, 6, MTL::IndexType::UInt32, index_buffer, 0);
    rc_encoder.EndEncoding();
    cmd_buffer.Present(Ctx.metal_context()->window().drawable());
    cmd_buffer.Commit();
    cmd_buffer.WaitUntilCompleted();
#endif

    display->swap_buffers();

    distance += step;
    if (distance >= 1 || distance <= -1) {
        step *= -1;
    }

    rotation += 0.05f;
    if (rotation > Math::Numbers::pi_v<float> * 2) {
        rotation = 0;
    }

#ifdef METAL
    Ctx.metal_context()->set_render_encoder(nullptr);
#endif
}

int main(int argc, char* argv[])
{
    display = Constructors::Display::construct(800, 600, "OpenRenderer");

    std::pair<std::string, int> position = { "position", 0 };

    if (METAL) {
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

#ifndef METAL
    auto va = Constructors::VertexArray::construct();
    auto vb = va->construct_vertex_buffer(vertexes.data(), vertexes.size() * sizeof(Math::Vector3f));
    vb->register_attribute_vec3(position.second, false, 0, 0);
    va->construct_index_buffer(indexes.data(), indexes.size());

    auto mesh = Mesh(va);
#else
    vertex_buffer = Ctx.metal_context()->device().NewBuffer(vertexes.data(), sizeof_data(vertexes), MTL::ResourceOptions::CpuCacheModeDefaultCache);
    index_buffer = Ctx.metal_context()->device().NewBuffer(indexes.data(), sizeof_data(indexes), MTL::ResourceOptions::CpuCacheModeDefaultCache);
#endif

    // --------------------------------------------
    main_loop->run();
    return EXIT_SUCCESS;
}