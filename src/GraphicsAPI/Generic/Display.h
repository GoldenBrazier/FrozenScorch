#pragma once
#include <string>

class Application;

namespace Generic {

class Display {
public:
    virtual ~Display() = default;

    virtual void swap_buffers() = 0;
    virtual bool closed() const = 0;

public:
    static void SetApplicationPointer(Application* app) { application_ptr = app; }

protected:
    static Application* GetApplicationPointer() { return application_ptr; }

protected:
    static Application* application_ptr;
};

}