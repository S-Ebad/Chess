#pragma once

#include "SDL3/SDL_pixels.h"
#include <SDL3/SDL_rect.h>
#include <array>
#include <filesystem>
#include <string_view>
#include <unordered_map>

namespace Config {
namespace fs = std::filesystem;

const auto IMAGES = fs::path{ASSETS_PATH} / "images";

constexpr std::string_view TITLE = "Chess";

// piece size (width & height)
constexpr SDL_Point PIECE_SIZE = {62, 62};

// window width & height
constexpr int WIDTH = 512;
constexpr int HEIGHT = 512;

// board dimensions
constexpr SDL_Point DIM = {.x = 8, .y = 8};

// square dimensions (pixels)
constexpr int SQUARE_W = WIDTH / DIM.x;
constexpr int SQUARE_H = HEIGHT / DIM.y;

constexpr std::array<SDL_Color, 2> COLORS = {
    SDL_Color{212, 223, 229, 255},
    SDL_Color{121, 156, 177, 255},
};

constexpr const char *STARTING_POS =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

const std::unordered_map<char, const char *> PIECE_TEXTURES{
    {'p', "bPawn.png"}, {'n', "bKnight.png"}, {'b', "bBishop.png"},
    {'r', "bRook.png"}, {'q', "bQueen.png"},  {'k', "bKing.png"},

    {'P', "wPawn.png"}, {'N', "wKnight.png"}, {'B', "wBishop.png"},
    {'R', "wRook.png"}, {'Q', "wQueen.png"},  {'K', "wKing.png"}};
} // namespace Config
