#pragma once

#include "types.hpp"
#include <SDL3/SDL.h>

class Piece {
public:
  Piece() : m_texture{nullptr}, m_type{PieceType::None}, m_side{Side::None} {}
  Piece(Piece &&other)
      : m_texture(other.m_texture), m_type(other.m_type), m_side(other.m_side) {
    other.m_texture = nullptr;
    other.m_side = Side::None;
    other.m_type = PieceType::None;
  }

  Piece(PieceType type, Side side, SDL_Texture *texture)
      : m_texture{texture}, m_type{type}, m_side{side} {}

  void draw(SDL_Renderer *renderer, SDL_Point position) const;

  PieceType get_type() const { return m_type; }
  Side get_side() const { return m_side; }

  Piece &operator=(Piece &&other) {
    this->m_texture = other.m_texture;
    this->m_side = other.m_side;
    this->m_type = other.m_type;

    other.m_texture = nullptr;
    other.m_side = Side::None;
    other.m_type = PieceType::None;

    return *this;
  }

private:
  SDL_Texture *m_texture;

  PieceType m_type;
  Side m_side;
};
