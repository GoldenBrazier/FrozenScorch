#pragma once
#include <GL/glew.h>
#include <memory>
#include <string>
#include <vector>

namespace GL {

class VarType {
public:
    enum class Type {
        None,
        Uniform,
    };

    VarType() = default;

    virtual ~VarType() = default;

    GLuint gl_id() const { return m_gl_id; }
    Type type() const { return m_type; }

protected:
    VarType(GLuint id, Type type)
        : m_type(type)
        , m_gl_id(id)
    {
    }

private:
    GLuint m_gl_id;
    Type m_type { Type::None };
};

class Float1 : public VarType {
public:
    Float1() = default;
    Float1(GLuint id, Type type)
        : VarType(id, type)
    {
    }

    Float1& operator=(float val)
    {
        if (type() == VarType::Type::Uniform) {
            glUniform1f(gl_id(), val);
        }
        return *this;
    }

    virtual ~Float1() = default;

private:
};

}