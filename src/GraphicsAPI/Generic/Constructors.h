#pragma once

#include <GraphicsAPI/Generic/Shader.h>
#include <GraphicsAPI/OpenGL/Shader.h>
#include <GraphicsAPI/Generic/Display.h>
#include <GraphicsAPI/OpenGL/Display.h>
#include <cassert>

#define CONSTRUCTIBLE_API_DEPENDENT(class_name)                                                           \
    namespace class_name {                                                                                \
    template <class... Args>                                                                              \
    inline std::shared_ptr<Generic::class_name> construct(Args&&... args)                                 \
    {                                                                                                     \
        if (true) {                                                                                       \
            return std::shared_ptr<Generic::class_name>(new GL::class_name(std::forward<Args>(args)...)); \
        }                                                                                                 \
        assert(false);                                                                                    \
    }                                                                                                     \
    }

namespace Constructors {

CONSTRUCTIBLE_API_DEPENDENT(Shader);
CONSTRUCTIBLE_API_DEPENDENT(Display);

}