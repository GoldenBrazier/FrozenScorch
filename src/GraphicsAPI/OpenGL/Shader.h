#pragma once
#include <GL/glew.h>
#include <GraphicsAPI/Generic/Shader.h>
#include <GraphicsAPI/Generic/ShaderVars.h>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace GL {

class Shader : public Generic::Shader {
public:
    Shader(const std::vector<std::string>& files);
    ~Shader();

    // Metal Constructor, which won't be called
    Shader(const std::string& file, const std::string& vert_func, const std::string& frag_func, const Generic::UniformList& uniforms, size_t uniforms_size) { std::abort(); }

    inline void compile() const override { }
    inline void bind() const override { glUseProgram(m_gl_program_id); }

    inline void set_uniform(const std::string& var_name, float fl) override;
    inline void set_uniform(const std::string& var_name, int val) override;
    inline void set_uniform(const std::string& var_name, const Math::Vector3f& vec3) override;
    inline void set_uniform(const std::string& var_name, const Math::Matrix4f& mat4) override;

    inline void set_uniform(const std::string& var_name, size_t index, float fl) override;
    inline void set_uniform(const std::string& var_name, size_t index, int val) override;
    inline void set_uniform(const std::string& var_name, size_t index, const Math::Vector3f& vec3) override;
    inline void set_uniform(const std::string& var_name, size_t index, const Math::Matrix4f& mat4) override;

    const std::string& name() const override { return m_name; }

protected:
    void set_name(const std::string& name) override { m_name = name; }

private:
    void prepare_program(const std::vector<std::string>& file_paths, const Generic::AttributeList& attributes, const Generic::UniformList& uniforms);
    void attach_shader(const std::string& text);
    GLuint get_shader_type(const std::string& path);
    GLuint create_shader(const std::string& path, GLenum shader_type);
    std::string load_shader(const std::string& filename);
    void check_shader_error(GLuint shader, GLuint flag, bool program, const std::string& errorMessage);
    void register_uniform_var(const std::string& uniform_name);
    std::string array_access_name(const std::string& name, size_t index) { return name + "[" + std::to_string(index) + "]"; }

    GLuint m_gl_program_id;
    std::vector<GLuint> m_gl_shaders_id {};
    std::unordered_map<std::string, GLuint> m_uniform_vars;
    std::string m_name;
};

void Shader::set_uniform(const std::string& var_name, float fl)
{
    if (m_uniform_vars.find(var_name) == m_uniform_vars.end()) {
        return;
    }
    glUniform1f(m_uniform_vars[var_name], fl);
}

void Shader::set_uniform(const std::string& var_name, int val)
{
    if (m_uniform_vars.find(var_name) == m_uniform_vars.end()) {
        return;
    }
    glUniform1i(m_uniform_vars[var_name], val);
}

void Shader::set_uniform(const std::string& var_name, const Math::Vector3f& vec3)
{
    if (m_uniform_vars.find(var_name) == m_uniform_vars.end()) {
        return;
    }
    glUniform3f(m_uniform_vars[var_name], vec3.x(), vec3.y(), vec3.z());
}

void Shader::set_uniform(const std::string& var_name, const Math::Matrix4f& mat4)
{
    if (m_uniform_vars.find(var_name) == m_uniform_vars.end()) {
        return;
    }
    glUniformMatrix4fv(m_uniform_vars[var_name], 1, GL_TRUE, mat4.data());
}

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