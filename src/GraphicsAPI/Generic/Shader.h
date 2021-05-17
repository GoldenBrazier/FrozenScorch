#pragma once

#include <GraphicsAPI/Var.h>
#include <Math/Matrix4f.h>
#include <Math/Vector3f.h>
#include <Utils.h>

namespace Generic {

class Shader {
public:
    virtual ~Shader() = default;

    virtual inline void compile() const = 0;
    virtual inline void bind() const = 0;

    virtual void set_uniform(const std::string& var_name, float fl) = 0;
    virtual void set_uniform(const std::string& var_name, const Math::Vector3f& vec3) = 0;
    virtual void set_uniform(const std::string& var_name, const Math::Matrix4f& mat4) = 0;
};

}