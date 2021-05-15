#pragma once
#include <Backend/OpenGL/VarTypes.h>
#include <Backend/Var.h>
#include <GL/glew.h>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace Backend {

class Shader {
public:
    Shader(const std::vector<std::string>& files, const std::vector<std::shared_ptr<Var>>& vars);
    ~Shader();

    inline void set_as_primary() const { glUseProgram(m_gl_program_id); }

    template <typename T>
    constexpr T get_uniform(const std::string& var_name)
    {
        static_assert(std::is_base_of_v<GL::VarType, T>);
        return T(m_uniform_vars[var_name], GL::VarType::Type::Uniform);
    }

private:
    void prepare_program(const std::vector<std::string>& files, const std::vector<std::shared_ptr<Var>>& vars);
    void attach_shader(const std::string& text);
    GLuint get_shader_type(const std::string& path);
    GLuint create_shader(const std::string& path, GLenum shader_type);
    std::string load_shader(const std::string& filename);
    void check_shader_error(GLuint shader, GLuint flag, bool program, const std::string& errorMessage);

    void register_uniform_var(std::shared_ptr<Uniform> uniform);

private:
    GLuint m_gl_program_id;
    std::vector<GLuint> m_gl_shaders_id {};
    std::unordered_map<std::string, GLuint> m_uniform_vars;
};

}