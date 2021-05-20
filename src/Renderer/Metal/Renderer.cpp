#include "Renderer.h"
#include <GraphicsAPI/Generic/Context.h>
#include <GraphicsAPI/Metal/IndexBuffer.h>
#include <GraphicsAPI/Metal/VertexArray.h>
#include <GraphicsAPI/Metal/VertexBuffer.h>

namespace Metal {

void Renderer::begin()
{
    m_command_buffer = Ctx.metal_context()->cmd_queue().CommandBuffer();
    auto renderpass_descriptor = Ctx.metal_context()->window().renderpass_descriptor();
    renderpass_descriptor.GetColorAttachments()[0].SetClearColor({ m_r, m_g, m_b, m_a });
    m_command_encoder = m_command_buffer.RenderCommandEncoder(renderpass_descriptor);

    Ctx.metal_context()->set_render_encoder(&m_command_encoder);
}

void Renderer::end()
{
    m_command_encoder.EndEncoding();
    m_command_buffer.Present(Ctx.metal_context()->window().drawable());
    m_command_buffer.Commit();
    m_command_buffer.WaitUntilCompleted();
}

void Renderer::set_clear_color(float r, float g, float b, float a)
{
    m_r = r;
    m_g = g;
    m_b = b;
    m_a = a;
}

void Renderer::draw_indexed(const std::shared_ptr<Generic::VertexArray>& va)
{
    auto vb_metal = std::static_pointer_cast<Metal::VertexBuffer>(va->vertex_buffer());
    auto ib_metal = std::static_pointer_cast<Metal::IndexBuffer>(va->index_buffer());

    m_command_encoder.SetVertexBuffer(vb_metal->buffer(), 0, 0);
    m_command_encoder.DrawIndexed(MTL::PrimitiveType::Triangle, ib_metal->count(), MTL::IndexType::UInt32, ib_metal->buffer(), 0);
}

}