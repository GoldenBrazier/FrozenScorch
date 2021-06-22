#pragma once
#include <GraphicsAPI/Generic/ShaderVars.h>
#include <Math/Matrix4f.h>
#include <Math/Vector3f.h>
#include <Utils.h>

#include <string>
#include <unordered_map>

namespace Generic {

class Shader {
public:
    virtual ~Shader() = default;

    virtual inline void compile() const = 0;
    virtual inline void bind() const = 0;

    //Vars
    virtual void set_uniform(const std::string& var_name, float fl) = 0;
    virtual void set_uniform(const std::string& var_name, int val) = 0;
    virtual void set_uniform(const std::string& var_name, const Math::Vector3f& vec3) = 0;
    virtual void set_uniform(const std::string& var_name, const Math::Matrix4f& mat4) = 0;

    //Arrays
    virtual void set_uniform(const std::string& var_name, size_t index, float fl) = 0;
    virtual void set_uniform(const std::string& var_name, size_t index, int val) = 0;
    virtual void set_uniform(const std::string& var_name, size_t index, const Math::Vector3f& vec3) = 0;
    virtual void set_uniform(const std::string& var_name, size_t index, const Math::Matrix4f& mat4) = 0;
};

class ShaderStorage {
public:
    ShaderStorage() = default;

    inline void add(const std::string& name, const std::shared_ptr<Shader>& shader)
    {
        m_shaders[name] = shader;
    }

    std::shared_ptr<Shader>& get(const std::string& name)
    {
        return m_shaders[name];
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders {};
};

}