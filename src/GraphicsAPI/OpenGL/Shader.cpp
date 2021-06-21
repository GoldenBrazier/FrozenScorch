#include <GraphicsAPI/OpenGL/Shader.h>
#include <GraphicsAPI/OpenGL/ShaderParser.h>
#include <fstream>
#include <iostream>
#include <string>

namespace GL {

Shader::Shader(const std::vector<std::string>& files)
    : Generic::Shader()
{
    auto parser = ShaderParser(files);
    parser.parse();
    prepare_program(files, parser.attributes(), parser.uniforms());
}

void Shader::prepare_program(const std::vector<std::string>& file_paths, const std::vector<std::pair<std::string, int>>& attributes, const Generic::UniformList& uniforms)
{
    m_gl_program_id = glCreateProgram();

    for (auto& path : file_paths) {
        attach_shader(path);
    }

    for (auto& attr : attributes) {
        glBindAttribLocation(m_gl_program_id, attr.second, attr.first.c_str());
    }

    glLinkProgram(m_gl_program_id);
    check_shader_error(m_gl_program_id, GL_LINK_STATUS, true, "Error linking shader program");

    for (auto& attr : attributes) {
        glBindAttribLocation(m_gl_program_id, attr.second, attr.first.c_str());
    }

    for (auto& unfs : uniforms) {
        register_uniform_var(unfs.name());
    }

    glValidateProgram(m_gl_program_id);
    check_shader_error(m_gl_program_id, GL_LINK_STATUS, true, "Invalid shader program");
}

Shader::~Shader()
{
    for (auto m_gl_shader_id : m_gl_shaders_id) {
        glDetachShader(m_gl_program_id, m_gl_shader_id);
        glDeleteShader(m_gl_shader_id);
    }
    glDeleteProgram(m_gl_program_id);
}

GLuint Shader::get_shader_type(const std::string& path)
{
    auto ends_with = [](const std::string& value, const std::string& ending) -> bool {
        if (ending.size() > value.size())
            return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    };

    if (ends_with(path, ".vs")) {
        return GL_VERTEX_SHADER;
    } else if (ends_with(path, ".fs")) {
        return GL_FRAGMENT_SHADER;
    }

    std::cerr << "Shader type is unknown: " << path << "\n";
    std::abort();
}

void Shader::attach_shader(const std::string& path)
{
    m_gl_shaders_id.push_back(create_shader(path, get_shader_type(path)));
    glAttachShader(m_gl_program_id, m_gl_shaders_id.back());
}

GLuint Shader::create_shader(const std::string& path, GLenum shader_type)
{
    const std::string& text = load_shader(path);
    auto gl_shader_id = glCreateShader(shader_type);

    const GLchar* shaderSourceStrings[] = { text.c_str() };
    GLint shaderSourceStringLengths[1] = { static_cast<GLint>(text.size()) };

    glShaderSource(gl_shader_id, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(gl_shader_id);

    check_shader_error(gl_shader_id, GL_COMPILE_STATUS, false, "Error: " + path + " compilation failed");

    return gl_shader_id;
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

void Shader::check_shader_error(GLuint shader, GLuint flag, bool program, const std::string& error_message)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if (program)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if (success == GL_FALSE) {
        if (program)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << error_message << ": " << error << std::endl;
        std::abort();
    }
}

void Shader::register_uniform_var(const std::string& uniform_name)
{
    // TODO(nikita): Add check for repeating names.
    auto m_gl_var_id = glGetUniformLocation(m_gl_program_id, uniform_name.c_str());
    if (m_gl_var_id == 0xFFFFFFFF) {
        std::cerr << "Can't find unifrom " << uniform_name;
        std::abort();
    }
    m_uniform_vars[uniform_name] = m_gl_var_id;
}

}