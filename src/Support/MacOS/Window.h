#pragma once
#include <mtlpp/mtlpp.hpp>

namespace Support::MacOS {

class Window {
public:
    Window(const MTL::Device& device, void (*render)(), size_t width, size_t height);

    size_t width() const;
    size_t height() const;
    MTL::Drawable drawable() const;
    MTL::RenderPassDescriptor renderpass_descriptor() const;

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