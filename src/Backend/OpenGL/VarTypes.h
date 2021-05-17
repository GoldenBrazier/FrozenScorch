#pragma once
#include <GL/glew.h>
#include <Math/Matrix4f.h>
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

class Float : public VarType {
public:
    Float() = default;
    Float(GLuint id, Type type)
        : VarType(id, type)
    {
    }

    virtual ~Float() = default;

    Float& operator=(float val)
    {
        if (type() == VarType::Type::Uniform) {
            glUniform1f(gl_id(), val);
        }
        return *this;
    }
};

class Vec3 : public VarType {
public:
    Vec3() = default;
    Vec3(GLuint id, Type type)
        : VarType(id, type)
    {
    }

    Vec3& operator=(const Vec3& val); // TODO: Implement me!

    virtual ~Vec3() = default;

private:
};

class Mat4 : public VarType {
public:
    Mat4(GLuint id, Type type)
        : VarType(id, type)
    {
    }

    virtual ~Mat4() = default;

    inline Mat4& operator=(const Math::Matrix4f& mat)
    {
        if (type() == VarType::Type::Uniform) {
            glUniformMatrix4fv(gl_id(), 1, GL_TRUE, mat.data());
        }
        return *this;
    }
};

}
