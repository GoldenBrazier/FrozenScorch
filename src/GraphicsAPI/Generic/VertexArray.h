#pragma once
#include <GraphicsAPI/Generic/IndexBuffer.h>
#include <GraphicsAPI/Generic/VertexBuffer.h>
#include <cstddef>
#include <memory>

namespace Generic {

class VertexArray {
public:
    virtual ~VertexArray() = default;

    virtual std::shared_ptr<VertexBuffer> construct_vertex_buffer(const void* data, size_t size) = 0;
    virtual std::shared_ptr<IndexBuffer> construct_index_buffer(const void* data, size_t count) = 0;

    virtual std::shared_ptr<VertexBuffer> vertex_buffer() = 0;
    virtual std::shared_ptr<IndexBuffer> index_buffer() = 0;
};

}