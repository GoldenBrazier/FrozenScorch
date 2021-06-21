#pragma once
#include <Utils.h>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

namespace Generic {

class Uniform {
public:
    Uniform(const std::string& name, size_t metal_offset = 0)
        : m_var_name(name)
        , m_metal_offset(metal_offset)
    {
    }

    ~Uniform() = default;

    const std::string& name() const { return  m_var_name; }
    size_t metal_offset() const { return m_metal_offset; }

private:
    std::string m_var_name;
    size_t m_metal_offset;
};

using UniformList = std::vector<Uniform>;

class UniformBuilder {
public:
    UniformBuilder() = default;
    ~UniformBuilder() = default;

    void add_var(const std::string& name, size_t metal_offset = 0) { m_data.emplace_back(name, metal_offset); }

    template <size_t ArrayLen, size_t ElementSize>
    void add_array(const std::string& name, size_t metal_offset = 0)
    {
        for (int i = 0; i < ArrayLen; i++) {
            std::ostringstream name_of_element;
            name_of_element << name << "[" << i << "]";
            m_data.emplace_back(name_of_element.str(), metal_offset);
            metal_offset += ElementSize;
        }
    }

    // FIXME: After metal parser is implemented we don't need this function.
    void add_gl_array(const std::string& name, size_t len)
    {
        for (int i = 0; i < len; i++) {
            std::ostringstream name_of_element;
            name_of_element << name << "[" << i << "]";
            m_data.emplace_back(name_of_element.str(), 0);
        }
    }

    const UniformList& data() const { return m_data; }

private:
    UniformList m_data;
};

}