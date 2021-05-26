#include "VertexArray.h"
#include "VertexBuffer.h"
#include <GraphicsAPI/Generic/Context.h>

namespace Metal {

std::shared_ptr<Generic::VertexBuffer> VertexArray::construct_vertex_buffer(const void* data, size_t size)
{
    m_vertex_buffer = VertexBuffer::construct(data, size);
    return m_vertex_buffer;
}

}