#include "Shader.h"
#include <fstream>
#include <iostream>
#include <string>

Shader::Shader(const std::string& filename)
{
    m_program = glCreateProgram();
    m_shaders[0] = create_shader(load_shader(filename + ".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = create_shader(load_shader(filename + ".fs"), GL_FRAGMENT_SHADER);

    for (size_t at = 0; at < NUM_SHADERS; at++) {
        glAttachShader(m_program, m_shaders[at]);
    }

    glBindAttribLocation(m_program, 0, "position");

    glLinkProgram(m_program);
    check_shader_error(m_program, GL_LINK_STATUS, true, "Error linking shader program");

    glValidateProgram(m_program);
    check_shader_error(m_program, GL_LINK_STATUS, true, "Invalid shader program");
}

Shader::~Shader()
{
    for (size_t at = 0; at < NUM_SHADERS; at++) {
        glDetachShader(m_program, m_shaders[at]);
        glDeleteShader(m_shaders[at]);
    }
    glDeleteProgram(m_program);
}

void Shader::bind()
{
    glUseProgram(m_program);
}

GLuint Shader::create_shader(const std::string& text, GLenum shader_type)
{
    auto shader = glCreateShader(shader_type);

    const GLchar* shaderSourceStrings[] = { text.c_str() };
    GLint shaderSourceStringLengths[1] = { static_cast<GLint>(text.size()) };

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    check_shader_error(shader, GL_COMPILE_STATUS, false, "Error: shader compilation failed: ");

    return shader;
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

void Shader::check_shader_error(GLuint shader, GLuint flag, bool program, const std::string& errorMessage)
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

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}