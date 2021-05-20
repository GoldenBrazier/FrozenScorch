#include "IndexBuffer.h"
#include <GraphicsAPI/Generic/Context.h>

namespace Metal {

IndexBuffer::IndexBuffer(const void* data, size_t count)
    : m_count(count)
{
    m_buffer = Ctx.metal_context()->device().NewBuffer(data, count * sizeof(uint32_t), MTL::ResourceOptions::CpuCacheModeDefaultCache);
}

}