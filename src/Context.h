#pragma once

#include <Backend/OpenGL/Context.h>
#include <memory>
#include <string>
#include <type_traits>

namespace GE {

enum class BackendType {
    OpenGL,
    Metal,
};

class Context {

private:
    template <BackendType T>
    struct context_return {
        typedef void* type;
    };

    template <>
    struct context_return<BackendType::OpenGL> {
        typedef GL::Context* type;
    };

public:
    Context() = default;
    ~Context() = default;

    template <BackendType T, typename U>
    inline constexpr void set_context(const std::shared_ptr<U>& context)
    {
        if constexpr (T == BackendType::OpenGL) {
            m_opengl_context = context;
        } else {
            []<bool flag = false>() { static_assert(flag, "Not supported Backend"); }
            ();
        }
    }

    template <BackendType T>
    inline constexpr typename context_return<T>::type context()
    {
        if constexpr (T == BackendType::OpenGL) {
            return m_opengl_context.get();
        } else {
            []<bool flag = false>() { static_assert(flag, "Not supported Backend"); }
            ();
        }
    }

private:
    std::shared_ptr<GL::Context> m_opengl_context;
};

}

extern GE::Context Context;