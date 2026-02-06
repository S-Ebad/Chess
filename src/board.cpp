#include "board.hpp"
#include "settings.hpp"
#include <SDL3/SDL.h>

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
