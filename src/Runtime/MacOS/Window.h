#pragma once

#include <mtlpp/mtlpp.hpp>

namespace Runtime::MacOS {

class Window {
public:
    Window(const mtlpp::Device& device, void (*render)(const Window&), size_t width, size_t height);

    size_t width() const;
    size_t height() const;
    mtlpp::Drawable drawable() const;
    mtlpp::RenderPassDescriptor renderpass_descriptor() const;

    static void Run();

private:
    class MtlView : public NS::Object {
    public:
        MtlView() = default;

        MtlView(const NS::Handle& handle)
            : NS::Object(handle)
        {
        }
    };

    MtlView m_view;
};

}