#include <GraphicsAPI/Generic/Context.h>
#include <GraphicsAPI/Metal/Shader.h>
#include <fstream>
#include <iostream>
#include <string>

namespace Metal {

Shader::Shader(const std::string& file, const std::string& vert_func, const std::string& frag_func, const std::vector<std::pair<std::string, int>>& uniforms, size_t uniforms_size)
    : Generic::Shader()
{
    prepare_program(file, vert_func, frag_func, uniforms, uniforms_size);
}

void Shader::prepare_program(const std::string& file, const std::string& vert_func_name, const std::string& frag_func_name, const std::vector<std::pair<std::string, int>>& uniforms, size_t uniforms_size)
{
    NS::Error error_buffer;
    auto& metal_device = Ctx.metal_context()->device();

    auto metal_shader = load_shader(file);
    MTL::Library library = metal_device.NewLibrary(metal_shader.c_str(), MTL::CompileOptions(), &error_buffer);
    if (!library.GetPtr()) {
        std::cout << error_buffer.GetLocalizedDescription().GetCStr() << std::endl;
        return;
    }

    if (!vert_func_name.empty()) {
        m_vert_func = library.NewFunction(vert_func_name.c_str());
        m_render_pipeline_desc.SetVertexFunction(m_vert_func);
    }
    if (!frag_func_name.empty()) {
        m_frag_func = library.NewFunction(frag_func_name.c_str());
        m_render_pipeline_desc.SetFragmentFunction(m_frag_func);
    }

    m_uniform_buffer = metal_device.NewBuffer(uniforms_size, MTL::ResourceOptions::CpuCacheModeDefaultCache);
    m_render_pipeline_desc.GetColorAttachments()[0].SetPixelFormat(MTL::PixelFormat::BGRA8Unorm);
    m_render_pipeline_desc.SetDepthAttachmentPixelFormat(MTL::PixelFormat::Depth32Float);
    m_render_pipeline_state = metal_device.NewRenderPipelineState(m_render_pipeline_desc, nullptr);

    m_depth_desc.SetDepthCompareFunction(MTL::CompareFunction::LessEqual);
    m_depth_desc.SetDepthWriteEnabled(true);
    m_depth_state = metal_device.NewDepthStencilState(m_depth_desc);

    for (auto& uni : uniforms) {
        register_uniform_var(uni);
    }

}

Shader::~Shader()
{
}

std::string Shader::load_shader(const std::string& filename)
{
    auto file = std::ifstream(filename);

    std::string output;
    std::string line;

    while (getline(file, line)) {
        output.append(line);
        output.append("\n");
    }

    return output;
}

void Shader::register_uniform_var(const std::pair<std::string, int>& uniform)
{
    // TODO(nikita): Add check for repeating names.
    m_uniform_vars[uniform.first] = uniform.second;
}

}