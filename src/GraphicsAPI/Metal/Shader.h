#pragma once
#include <GraphicsAPI/Generic/Shader.h>
#include <GraphicsAPI/Generic/ShaderVars.h>
#include <iostream>
#include <memory>
#include <mtlpp/mtlpp.hpp>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace Metal {

class Shader : public Generic::Shader {
public:
    Shader(const std::string& file, const std::string& vert_func, const std::string& frag_func, const Generic::UniformList& uniforms, size_t uniforms_size);
    ~Shader();

    // OpenGL Constructor, which won't be called
    Shader(const std::vector<std::string>& files) { std::abort(); }

    inline void compile() const override { }
    inline void bind() const override
    {
        auto rc_encoder = Ctx.metal_context()->render_encoder();
        rc_encoder->SetRenderPipelineState(m_render_pipeline_state);
        rc_encoder->SetDepthStencilState(m_depth_state);
        rc_encoder->SetVertexBuffer(m_uniform_buffer, 0, 1);
        rc_encoder->SetFragmentBuffer(m_uniform_buffer, 0, 1);
    }

    inline void set_uniform(const std::string& var_name, float fl) override;
    inline void set_uniform(const std::string& var_name, int val) override;
    inline void set_uniform(const std::string& var_name, const Math::Vector3f& vec3) override;
    inline void set_uniform(const std::string& var_name, const Math::Matrix4f& mat4) override;

    inline void set_uniform(const std::string& var_name, size_t index, float fl) override;
    inline void set_uniform(const std::string& var_name, size_t index, int val) override;
    inline void set_uniform(const std::string& var_name, size_t index, const Math::Vector3f& vec3) override;
    inline void set_uniform(const std::string& var_name, size_t index, const Math::Matrix4f& mat4) override;

private:
    void prepare_program(const std::string& file, const std::string& vert_func, const std::string& frag_func, const Generic::UniformList& uniforms, size_t uniforms_size);
    std::string load_shader(const std::string& filename);
    void register_uniform_var(const Generic::Uniform& uniform);

    std::string array_access_name(const std::string& name, size_t index) { return name + "[" + std::to_string(index) + "]"; }

private:
    MTL::RenderPipelineState m_render_pipeline_state;
    MTL::DepthStencilState m_depth_state;
    std::unordered_map<std::string, size_t> m_uniform_vars;
    MTL::Buffer m_uniform_buffer;
    MTL::RenderPipelineDescriptor m_render_pipeline_desc;
    MTL::DepthStencilDescriptor m_depth_desc;
    MTL::Function m_vert_func;
    MTL::Function m_frag_func;
};

void Shader::set_uniform(const std::string& var_name, float fl)
{
    if (m_uniform_vars.find(var_name) == m_uniform_vars.end()) {
        return;
    }
    char* ptr = ((char*)m_uniform_buffer.GetContents() + m_uniform_vars[var_name]);
    memcpy(ptr, &fl, sizeof(float));
}

void Shader::set_uniform(const std::string& var_name, int val)
{
    if (m_uniform_vars.find(var_name) == m_uniform_vars.end()) {
        return;
    }
    char* ptr = ((char*)m_uniform_buffer.GetContents() + m_uniform_vars[var_name]);
    memcpy(ptr, &val, sizeof(int));
}

void Shader::set_uniform(const std::string& var_name, const Math::Vector3f& vec3)
{
    if (m_uniform_vars.find(var_name) == m_uniform_vars.end()) {
        return;
    }
    char* ptr = ((char*)m_uniform_buffer.GetContents() + m_uniform_vars[var_name]);
    memcpy(ptr, vec3.data(), sizeof(Math::Vector3f));
}

void Shader::set_uniform(const std::string& var_name, const Math::Matrix4f& mat4)
{
    if (m_uniform_vars.find(var_name) == m_uniform_vars.end()) {
        return;
    }
    char* ptr = ((char*)m_uniform_buffer.GetContents() + m_uniform_vars[var_name]);
    memcpy(ptr, mat4.data(), sizeof(Math::Matrix4f));
}

//TODO: It's possible to validate all array accesses, but currently we don't.
void Shader::set_uniform(const std::string& var_name, size_t index, float fl)
{
    set_uniform(array_access_name(var_name, index), fl);
}

void Shader::set_uniform(const std::string& var_name, size_t index, int val)
{
    set_uniform(array_access_name(var_name, index), val);
}

void Shader::set_uniform(const std::string& var_name, size_t index, const Math::Vector3f& vec3)
{
    set_uniform(array_access_name(var_name, index), vec3);
}

void Shader::set_uniform(const std::string& var_name, size_t index, const Math::Matrix4f& mat4)
{
    set_uniform(array_access_name(var_name, index), mat4);
}

}