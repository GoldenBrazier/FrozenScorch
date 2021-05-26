#pragma once
#include <GraphicsAPI/Generic/Display.h>
#include <GraphicsAPI/Generic/IndexBuffer.h>
#include <GraphicsAPI/Generic/MainLoop.h>
#include <GraphicsAPI/Generic/Shader.h>
#include <GraphicsAPI/Generic/Texture.h>
#include <GraphicsAPI/Generic/VertexArray.h>
#include <GraphicsAPI/Generic/VertexBuffer.h>
#include <GraphicsAPI/Metal/Display.h>
#include <GraphicsAPI/Metal/IndexBuffer.h>
#include <GraphicsAPI/Metal/MainLoop.h>
#include <GraphicsAPI/Metal/Shader.h>
#include <GraphicsAPI/Metal/Texture.h>
#include <GraphicsAPI/Metal/VertexArray.h>
#include <GraphicsAPI/Metal/VertexBuffer.h>
#include <GraphicsAPI/OpenGL/Display.h>
#include <GraphicsAPI/OpenGL/IndexBuffer.h>
#include <GraphicsAPI/OpenGL/MainLoop.h>
#include <GraphicsAPI/OpenGL/Shader.h>
#include <GraphicsAPI/OpenGL/Texture.h>
#include <GraphicsAPI/OpenGL/VertexArray.h>
#include <GraphicsAPI/OpenGL/VertexBuffer.h>
#include <Renderer/Metal/Renderer.h>
#include <Renderer/OpenGL/Renderer.h>
#include <cassert>

// #define METAL true

#define CONSTRUCTIBLE_API_DEPENDENT(class_name)                                                              \
    namespace class_name {                                                                                   \
    template <class... Args>                                                                                 \
    inline std::shared_ptr<Generic::class_name> construct(Args&&... args)                                    \
    {                                                                                                        \
        if (Ctx.graphics_api_type() == Generic::GraphicsAPIType::Metal) {                                    \
            return std::shared_ptr<Generic::class_name>(new Metal::class_name(std::forward<Args>(args)...)); \
        } else {                                                                                             \
            return std::shared_ptr<Generic::class_name>(new GL::class_name(std::forward<Args>(args)...));    \
        }                                                                                                    \
        assert(false);                                                                                       \
    }                                                                                                        \
    }

namespace Constructors {

CONSTRUCTIBLE_API_DEPENDENT(Shader);
CONSTRUCTIBLE_API_DEPENDENT(Display);
CONSTRUCTIBLE_API_DEPENDENT(MainLoop);
CONSTRUCTIBLE_API_DEPENDENT(IndexBuffer);
CONSTRUCTIBLE_API_DEPENDENT(VertexBuffer);
CONSTRUCTIBLE_API_DEPENDENT(VertexArray);
CONSTRUCTIBLE_API_DEPENDENT(Renderer);
CONSTRUCTIBLE_API_DEPENDENT(Texture);

}