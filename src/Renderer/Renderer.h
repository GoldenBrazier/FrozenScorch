#pragma once

#include <GraphicsAPI/Generic/Shader.h>
#include <GraphicsAPI/Generic/VertexArray.h>
#include <Model.h>
#include <memory>
#include <string>

class Camera;

namespace Generic {

class Renderer {
public:
    // Scene
    void begin_scene(const Camera& camera);
    void end_scene();

protected:
    // GraphicsAPI specific function.
    virtual void begin() {};
    virtual void end() {};

public:
    // Draw
    virtual void set_clear_color(float r, float g, float b, float a) = 0;
    virtual void clear() {};

    virtual void draw_indexed(const std::shared_ptr<Generic::VertexArray>& va) = 0;

    void draw_model(const Model& model, const std::shared_ptr<Generic::Shader>& shader, const Math::Matrix4f& transform);

private:
    const Camera* m_camera {};
};

}