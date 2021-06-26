#pragma once
#include <GraphicsAPI/Generic/ShaderVars.h>
#include <Math/Matrix4f.h>
#include <Math/Vector3f.h>
#include <Utils.h>

#include <string>
#include <unordered_map>

namespace Generic {

class ShaderStorage;

class Shader {
    friend ShaderStorage;

public:
    virtual ~Shader() = default;

    virtual inline void compile() const = 0;
    virtual inline void bind() const = 0;
    virtual const std::string& name() const = 0;

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

protected:
    virtual void set_name(const std::string& name) = 0;
};

class ShaderStorage {
public:
    ShaderStorage() = default;

    inline void add(const std::string& name, const std::shared_ptr<Shader>& shader)
    {
        shader->set_name(name);
        m_shaders[name] = shader;
    }

    std::shared_ptr<Shader>& get(const std::string& name)
    {
        return m_shaders[name];
    }

    std::vector<std::string> names()
    {
        std::vector<std::string> res;
        for (auto& i : m_shaders) {
            res.push_back(i.first);
        }
        return res;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders {};
};

}