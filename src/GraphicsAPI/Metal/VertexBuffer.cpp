#include "VertexBuffer.h"
#include <GraphicsAPI/Generic/Context.h>

namespace Metal {

VertexBuffer::VertexBuffer(std::vector<Generic::Vertex>&& data)
    : m_verteces(std::move(data))
{
    size_t size = sizeof(std::vector<Generic::Vertex>::value_type) * m_verteces.size();
    m_buffer = Ctx.metal_context()->device().NewBuffer(m_verteces.data(), size, MTL::ResourceOptions::CpuCacheModeDefaultCache);
}

// void VertexBuffer::bind()
// {
//     auto cmd_buffer = Ctx.metal_context()->cmd_queue().CommandBuffer();
//     auto rc_encoder = cmd_buffer.RenderCommandEncoder(renderpass_descriptor);
// }

}