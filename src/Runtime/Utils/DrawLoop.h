#pragma once

#include <Runtime/Debug/Debug.h>
#include <chrono>
#include <iostream>

namespace Runtime {

template <Debug DebugLevel = Debug::Off, typename Callback>
constexpr void DrawLoop(int fps, Callback callback)
{
    bool cont = true;
    while (cont) {
        std::chrono::steady_clock::time_point begin_time, end_time;
        if constexpr (DebugLevel >= Debug::Level1) {
            begin_time = std::chrono::steady_clock::now();
        }
        cont = !callback();
        if constexpr (DebugLevel >= Debug::Level1) {
            end_time = std::chrono::steady_clock::now();
            auto diff = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count());
            std::cout << "Frame took: " << diff / 1000.0 << "[s]" << std::endl;
        }
    }
}

}