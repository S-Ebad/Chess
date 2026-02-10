#pragma once

#include "types.hpp"
#include <SDL3/SDL.h>

class Piece {
public:
  Piece() : m_texture{nullptr}, m_type{PieceType::None}, m_side{Side::None} {}
  Piece(PieceType type, Side side, SDL_Texture *texture)
      : m_texture{texture}, m_type{type}, m_side{side} {}

  void draw(SDL_Renderer *renderer, SDL_Point position) const;

  PieceType get_type() const {
    return m_type;
  }

  Side get_side() const {
    return m_side;
  }

private:
  SDL_Texture *m_texture;

  PieceType m_type;
  Side m_side;
};
