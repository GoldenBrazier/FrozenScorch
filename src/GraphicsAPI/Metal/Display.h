#pragma once
#include <GraphicsAPI/Generic/Display.h>
#include <mtlpp/mtlpp.hpp>
#include <string>

namespace Metal {

class Display : public Generic::Display {
public:
    Display(size_t width, size_t height, const std::string& name);

    void swap_buffers() override {};
    bool closed() const override { return false; }

    static void draw_cycle_callback();
    static void key_up_callback(int a, int b);
    static void key_down_callback(int a, int b);
    static void mouse_move_callback(float a, float b);
    static void mouse_down_callback(int a, int b);
};

}