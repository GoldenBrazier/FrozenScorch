cmake_minimum_required(VERSION 3.17)
project(OpenRenderer)

enable_language(OBJC)

set(CMAKE_OBJC_FLAGS "-mmacosx-version-min=10.12")
set(CMAKE_CXX_FLAGS "-std=c++2a -Isrc -Ires -IDependencies/Code -ggdb")
set(CMAKE_EXE_LINKER_FLAGS "-framework ServiceManagement -framework Foundation -framework Cocoa -framework Metal -framework MetalKit -framework Cocoa -framework CoreFoundation -fobjc-link-runtime")

add_subdirectory(Dependencies/Libraries/SDL)
add_subdirectory(Dependencies/Libraries/glew)

include_directories(src)
include_directories(Dependencies/Code)
include_directories(res)
include_directories(Dependencies/Libraries/SDL/include)
include_directories(Dependencies/Libraries/glew/include)

add_executable(OpenRenderer ./Dependencies/Code/imgui/imgui_widgets.cpp
./Dependencies/Code/imgui/imgui.cpp
./Dependencies/Code/imgui/imgui_impl_opengl3.cpp
./Dependencies/Code/imgui/imgui_tables.cpp
./Dependencies/Code/imgui/imgui_demo.cpp
./Dependencies/Code/imgui/imgui_impl_sdl.cpp
./Dependencies/Code/imgui/imgui_draw.cpp
./Dependencies/Code/mtlpp/src/texture.mm
./Dependencies/Code/mtlpp/src/stage_input_output_descriptor.mm
./Dependencies/Code/mtlpp/src/buffer.mm
./Dependencies/Code/mtlpp/src/compute_command_encoder.mm
./Dependencies/Code/mtlpp/src/render_pass.mm
./Dependencies/Code/mtlpp/src/blit_command_encoder.mm
./Dependencies/Code/mtlpp/src/depth_stencil.mm
./Dependencies/Code/mtlpp/src/render_pipeline.mm
./Dependencies/Code/mtlpp/src/function_constant_values.mm
./Dependencies/Code/mtlpp/src/command_queue.mm
./Dependencies/Code/mtlpp/src/sampler.mm
./Dependencies/Code/mtlpp/src/parallel_render_command_encoder.mm
./Dependencies/Code/mtlpp/src/command_buffer.mm
./Dependencies/Code/mtlpp/src/library.mm
./Dependencies/Code/mtlpp/src/heap.mm
./Dependencies/Code/mtlpp/src/argument.mm
./Dependencies/Code/mtlpp/src/render_command_encoder.mm
./Dependencies/Code/mtlpp/src/ns.mm
./Dependencies/Code/mtlpp/src/command_encoder.mm
./Dependencies/Code/mtlpp/src/resource.mm
./Dependencies/Code/mtlpp/src/compute_pipeline.mm
./Dependencies/Code/mtlpp/src/vertex_descriptor.mm
./Dependencies/Code/mtlpp/src/device.mm
./Dependencies/Code/mtlpp/src/fence.mm
./Dependencies/Code/mtlpp/src/drawable.mm
./Dependencies/Code/lodepng/lodepng.cpp
./src/Mesh.cpp
./src/Model.cpp
./src/main.cpp
./src/Renderer/Renderer.cpp
./src/Renderer/Metal/Renderer.cpp
./src/Renderer/OpenGL/Renderer.cpp
./src/Parsers/ObjParser.cpp
./src/Math/Vector3f.cpp
./src/Math/Matrix4f.cpp
./src/Support/MacOS/Window.mm
./src/Application/Camera.cpp
./src/Application/Application.cpp
./src/Scene/Scene.cpp
./src/GraphicsAPI/Metal/VertexBuffer.cpp
./src/GraphicsAPI/Metal/VertexArray.cpp
./src/GraphicsAPI/Metal/Texture.cpp
./src/GraphicsAPI/Metal/Display.cpp
./src/GraphicsAPI/Metal/Shader.cpp
./src/GraphicsAPI/Metal/IndexBuffer.cpp
./src/GraphicsAPI/Generic/Context.cpp
./src/GraphicsAPI/Generic/Display.cpp
./src/GraphicsAPI/OpenGL/VertexBuffer.cpp
./src/GraphicsAPI/OpenGL/VertexArray.cpp
./src/GraphicsAPI/OpenGL/Display.cpp
./src/GraphicsAPI/OpenGL/Shader.cpp
./src/GraphicsAPI/OpenGL/ShaderParser.cpp
./src/GraphicsAPI/OpenGL/IndexBuffer.cpp
./src/Editor/Editor.cpp
        src/Editor/OpenGL/Editor.h)

target_link_libraries (
    OpenRenderer
    SDL2main SDL2-static
    libglew_static
)

file (
    COPY
    res
    DESTINATION
    ${CMAKE_CURRENT_BINARY_DIR}/
)
