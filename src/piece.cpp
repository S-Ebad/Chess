#include "piece.hpp"
#include "settings.hpp"

void Piece::draw(SDL_Renderer *renderer, SDL_Point position) {
  if (m_type == PieceType::None || m_side == Side::None) {
    return;
  }

  SDL_FRect dst{.x = static_cast<float>(position.x),
                .y = static_cast<float>(position.y),
                .w = static_cast<float>(Config::PIECE_SIZE.x),
                .h = static_cast<float>(Config::PIECE_SIZE.y)};

  SDL_RenderTexture(renderer, m_texture, nullptr, &dst);
}
