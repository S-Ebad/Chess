#pragma once

#include "SDL3/SDL_render.h"
#include "piece.hpp"
#include <array>

class Board {
public:
  Board() : m_pieces{} {}

  static void draw_board(SDL_Renderer *renderer);

private:
  std::array<Piece, 64> m_pieces;
};
