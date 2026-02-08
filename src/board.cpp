#include "board.hpp"
#include "settings.hpp"
#include <SDL3/SDL.h>

Board::Board() : m_pieces{}, manager{Config::IMAGES} {}

void Board::load_textures(SDL_Renderer *renderer) {
  manager.add_asset(renderer, "bBishop.png");
}

void Board::draw_pieces(SDL_Renderer *renderer) {
  SDL_Texture *texture = manager.get_asset("bBishop.png");

  SDL_FRect dst = {.x = 0,
                   .y = 0,
                   .w = 62,
                   .h = 62};

  SDL_RenderTexture(renderer, texture, NULL, &dst);
}

void Board::draw_board(SDL_Renderer *renderer) {

  SDL_FRect rect{.x = 0.f,
                 .y = 0.f,
                 .w = static_cast<float>(Config::SQUARE_W),
                 .h = static_cast<float>(Config::SQUARE_H)};

  SDL_Color color;

  for (int i = 0; i < (Config::DIM_X * Config::DIM_Y); i++) {
    int row = i / Config::DIM_X;
    int col = i % Config::DIM_X;

    color = Config::COLORS[static_cast<size_t>((row + col) % 2)];

    rect.x = static_cast<float>(row * Config::SQUARE_W);
    rect.y = static_cast<float>(col * Config::SQUARE_H);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
  }
}
