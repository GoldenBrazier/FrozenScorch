#include "VertexArray.h"
#include "VertexBuffer.h"
#include <GraphicsAPI/Generic/Context.h>

namespace Metal {

std::shared_ptr<Generic::VertexBuffer> VertexArray::construct_vertex_buffer(std::vector<Generic::Vertex>&& data)
{
    m_vertex_buffer = VertexBuffer::construct(std::move(data));
    return m_vertex_buffer;
}

}