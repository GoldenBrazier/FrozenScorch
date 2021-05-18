#pragma once
#include <string>

namespace Generic {

class Display {
public:
    virtual ~Display() = default;

    virtual void swap_buffers() = 0;
    virtual bool closed() const = 0;

private:
};

}