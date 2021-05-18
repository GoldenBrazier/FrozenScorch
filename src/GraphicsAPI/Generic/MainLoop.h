#pragma once
#include <cstddef>
#include <cstdint>

namespace Generic {

class MainLoop {
public:
    virtual ~MainLoop() = default;

    virtual void run() = 0;
};

}