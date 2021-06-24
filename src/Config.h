#pragma once

#include <string>

namespace Config {

static const char* ModelsFolder = "res/models";
static const char* GLSL_VERSION = "#version 330 core";

constexpr size_t ComponentCount = 32;
constexpr size_t SystemCount = 8;

constexpr size_t SCREEN_WIDTH = 1280;
constexpr size_t SCREEN_HEIGHT = 720;

}