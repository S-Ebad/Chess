#pragma once

#include "SDL3/SDL_render.h"
#include "assetmanager.hpp"
#include "piece.hpp"
#include <array>

class Board {
public:
  Board();

  void load_textures(SDL_Renderer *renderer);

  void draw_pieces(SDL_Renderer *renderer);
  static void draw_board(SDL_Renderer *renderer);

private:
  std::array<Piece, 64> m_pieces;
  AssetManager manager;
};
