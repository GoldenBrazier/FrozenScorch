#pragma once
#include <GL/glew.h>
#include <GraphicsAPI/Generic/Shader.h>
#include <GraphicsAPI/Generic/Var.h>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace GL {

class Shader : public Generic::Shader {
public:
    Shader(const std::vector<std::string>& files, const std::vector<std::pair<std::string, int>>& attributes, const std::vector<std::string>& uniforms);
    ~Shader();

    // Metal Constructor, which won't be called
    Shader(const std::string& file, const std::string& vert_func, const std::string& frag_func, const std::vector<std::pair<std::string, int>>& uniforms, size_t uniforms_size) { std::abort(); }

    inline void compile() const override { }
    inline void bind() const override { glUseProgram(m_gl_program_id); }

    inline void set_uniform(const std::string& var_name, float fl) override;
    inline void set_uniform(const std::string& var_name, const Math::Vector3f& vec3) override;
    inline void set_uniform(const std::string& var_name, const Math::Matrix4f& mat4) override;

private:
    void prepare_program(const std::vector<std::string>& file_paths, const std::vector<std::pair<std::string, int>>& attributes, const std::vector<std::string>& uniforms);
    void attach_shader(const std::string& text);
    GLuint get_shader_type(const std::string& path);
    GLuint create_shader(const std::string& path, GLenum shader_type);
    std::string load_shader(const std::string& filename);
    void check_shader_error(GLuint shader, GLuint flag, bool program, const std::string& errorMessage);
    void register_uniform_var(const std::string& uniform_name);

private:
    GLuint m_gl_program_id;
    std::vector<GLuint> m_gl_shaders_id {};
    std::unordered_map<std::string, GLuint> m_uniform_vars;
};

void Shader::set_uniform(const std::string& var_name, float fl)
{
    if (m_uniform_vars.find(var_name) == m_uniform_vars.end()) {
        return;
    }
    glUniform1f(m_uniform_vars[var_name], fl);
}

void Shader::set_uniform(const std::string& var_name, const Math::Vector3f& vec3)
{
}

void Shader::set_uniform(const std::string& var_name, const Math::Matrix4f& mat4)
{
    if (m_uniform_vars.find(var_name) == m_uniform_vars.end()) {
        return;
    }
    glUniformMatrix4fv(m_uniform_vars[var_name], 1, GL_TRUE, mat4.data());
}

}