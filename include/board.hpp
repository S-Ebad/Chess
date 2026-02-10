#pragma once

#include "SDL3/SDL_render.h"
#include "assetmanager.hpp"
#include "piece.hpp"
#include "settings.hpp"
#include <array>

class Board {
public:
  // board takes renderer so it can load all the assets
  Board();

  void load_fen(const AssetManager &manager, const std::string_view fen);

  void draw_pieces(SDL_Renderer *renderer);
  static void draw_board(SDL_Renderer *renderer);

  static constexpr inline int to_idx(int row, int col) {
    return row * Config::DIM.x + col;
  }

  // row
  static constexpr inline int rank(int idx) { return idx / Config::DIM.x; }

  // column
  static constexpr inline int file(int idx) { return (idx % Config::DIM.x); }

  static constexpr inline char file_char(int idx) {
    return static_cast<char>(idx / Config::DIM.x) + 'a';
  }

private:
  Side m_turn;
  std::array<Piece, 64> m_pieces;
};
