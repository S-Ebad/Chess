#pragma once

#include "SDL3/SDL_pixels.h"
#include <array>
#include <string_view>
#include <filesystem>

namespace Config {
namespace fs = std::filesystem;

const auto IMAGES = fs::path{ASSETS_PATH} / "images";

constexpr std::string_view TITLE = "Chess";

// window width & height
constexpr int WIDTH = 512;
constexpr int HEIGHT = 512;

// board dimensions
constexpr int DIM_X = 8;
constexpr int DIM_Y = 8;

// square dimensions (pixels)
constexpr int SQUARE_W = WIDTH / DIM_X;
constexpr int SQUARE_H = HEIGHT / DIM_Y;

constexpr std::array<SDL_Color, 2> COLORS = {SDL_Color{121, 156, 177, 255},
                                             SDL_Color{212, 223, 229, 255}};
} // namespace Config
