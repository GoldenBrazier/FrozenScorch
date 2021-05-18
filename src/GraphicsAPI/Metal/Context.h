#pragma once
#include <Support/MacOS/Window.h>
#include <Utils.h>
#include <mtlpp/mtlpp.hpp>

namespace Metal {

class Context {
    CONSTRUCTIBLE(Context);

public:
    explicit Context(const MTL::Device& device)
        : m_device(device)
    {
        m_cmd_queue = m_device.NewCommandQueue();
    }

    ~Context() = default;

    MTL::Device& device() { return m_device; }
    const MTL::Device& device() const { return m_device; }

    MTL::CommandQueue& cmd_queue() { return m_cmd_queue; }
    const MTL::CommandQueue& cmd_queue() const { return m_cmd_queue; }

    void set_window(Support::MacOS::Window* win) { m_window = win; }
    Support::MacOS::Window& window() { return *m_window; }
    const Support::MacOS::Window& window() const { return *m_window; }

    void set_render_encoder(MTL::RenderCommandEncoder* en) { m_render_encoder = en; }
    MTL::RenderCommandEncoder* render_encoder() { return m_render_encoder; }

private:
    MTL::Device m_device;
    MTL::CommandQueue m_cmd_queue;
    Support::MacOS::Window* m_window;
    MTL::RenderCommandEncoder* m_render_encoder { nullptr };
};

}