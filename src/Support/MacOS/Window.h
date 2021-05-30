#pragma once
#include <mtlpp/mtlpp.hpp>

namespace Support::MacOS {

class Window {
public:
    Window(const MTL::Device& device, size_t width, size_t height);

    size_t width() const;
    size_t height() const;
    MTL::Drawable drawable() const;
    MTL::RenderPassDescriptor renderpass_descriptor() const;
    
    void set_draw_callback(void (*drawcallback)());
    void set_key_up_callback(void (*key_callback)(int, int));
    void set_key_down_callback(void (*key_callback)(int, int));
    void set_mouse_down_callback(void (*mouse_down_callback)(int, int));
    void set_mouse_move_callback(void (*mouse_move_callback)(float, float));

    static void Run();

private:
    class NSLink : public NS::Object {
    public:
        NSLink() = default;

        NSLink(const NS::Handle& handle)
            : NS::Object(handle)
        {
        }
    };

    NSLink m_view;
    NSLink m_view_controller;
};

}