#include "VertexBuffer.h"
#include <GraphicsAPI/Generic/Context.h>

namespace Metal {

VertexBuffer::VertexBuffer(const void* data, size_t size)
{
    m_buffer = Ctx.metal_context()->device().NewBuffer(data, size, MTL::ResourceOptions::CpuCacheModeDefaultCache);
}

// void VertexBuffer::bind()
// {
//     auto cmd_buffer = Ctx.metal_context()->cmd_queue().CommandBuffer();
//     auto rc_encoder = cmd_buffer.RenderCommandEncoder(renderpass_descriptor);
// }

}