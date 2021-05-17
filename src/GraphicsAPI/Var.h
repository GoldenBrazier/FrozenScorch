#pragma once
#include <Utils.h>
#include <memory>
#include <string>
#include <vector>

namespace Generic {

class Var {
    friend class Attribute;
    friend class Uniform;

public:
    enum class Type {
        None,
        Attribute,
        Uniform,
    };

    virtual ~Var() = default;

    bool is_attribute() const { return type() == Type::Attribute; }
    bool is_uniform() const { return type() == Type::Uniform; }

    const std::string& name() const { return m_name; }
    Type type() const { return m_type; }

protected:
    Var() = default;
    Var(const std::string& name, Type type)
        : m_type(type)
        , m_name(name)
    {
    }

    Var(std::string&& name, Type type)
        : m_type(type)
        , m_name(std::move(name))
    {
    }

private:
    std::string m_name {};
    Type m_type { Type::None };
};

class Attribute : public Var {
    CONSTRUCTIBLE(Attribute)

public:
    virtual ~Attribute() = default;

    size_t index() const { return m_index; }

protected:
    Attribute() = default;
    Attribute(const std::string& name, size_t index)
        : Var(name, Var::Type::Attribute)
        , m_index(index)
    {
    }

private:
    size_t m_index;
};

class Uniform : public Var {
    CONSTRUCTIBLE(Uniform)

public:
    virtual ~Uniform() = default;

protected:
    Uniform() = default;
    Uniform(const std::string& name)
        : Var(name, Var::Type::Uniform)
    {
    }
};

}