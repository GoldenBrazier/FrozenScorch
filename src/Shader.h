#pragma once
#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader(const std::string& filename);
    ~Shader();
    void bind();

private:
    GLuint create_shader(const std::string& text, GLenum shader_type);
    std::string load_shader(const std::string& filename);
    void check_shader_error(GLuint shader, GLuint flag, bool program, const std::string& errorMessage);

private:
    static constexpr auto NUM_SHADERS = 2;
    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
};