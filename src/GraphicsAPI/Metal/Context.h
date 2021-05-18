#pragma once
#include <Utils.h>
#include <mtlpp/mtlpp.hpp>

namespace Metal {

class Context {
    CONSTRUCTIBLE(Context);

public:
    explicit Context(const MTL::Device& device)
        : m_device(device)
    {
        m_cmd_queue = m_device.NewCommandQueue();
    }

    ~Context() = default;

    MTL::Device& device() { return m_device; }
    const MTL::Device& device() const { return m_device; }

    MTL::CommandQueue& cmd_queue() { return m_cmd_queue; }
    const MTL::CommandQueue& cmd_queue() const { return m_cmd_queue; }

private:
    MTL::Device m_device;
    MTL::CommandQueue m_cmd_queue;
};

}