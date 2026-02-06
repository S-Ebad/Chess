#pragma once

#include "SDL3/SDL_render.h"

class Board {
public:
  Board() = default;

  static void draw_board(SDL_Renderer *renderer);

private:
};
