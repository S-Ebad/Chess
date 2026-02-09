#pragma once

#include "SDL3/SDL_render.h"
#include "assetmanager.hpp"
#include "piece.hpp"
#include "settings.hpp"
#include <array>

class Board {
public:
  Board() : m_pieces{}, manager{Config::IMAGES} {};

  // board takes renderer so it can load all the assets
  Board(SDL_Renderer *renderer, std::string_view fen);

  // void load_textures(SDL_Renderer *renderer);

  void draw_pieces(SDL_Renderer *renderer);
  static void draw_board(SDL_Renderer *renderer);

  static constexpr inline int to_idx(int row, int col) {
    return row * Config::DIM.x + col;
  }

  // row
  static constexpr inline int rank(int idx) {
    return idx / Config::DIM.x;
  }

  // column
  static constexpr inline int file(int idx) {
    return (idx % Config::DIM.x);
  }

  static constexpr inline char file_char(int idx) {
    return (idx / Config::DIM.x) + 'a';
  }

private:
  void parse_fen(SDL_Renderer *renderer, std::string_view fen);

private:
  std::array<Piece, 64> m_pieces;
  AssetManager manager;
};
