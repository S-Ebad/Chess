#include "board.hpp"
#include "settings.hpp"
#include <SDL3/SDL.h>

Board::Board(SDL_Renderer *renderer, std::string_view fen) : m_pieces{}, manager{Config::IMAGES} {
  this->parse_fen(renderer, fen);
}

void Board::parse_fen(SDL_Renderer *renderer, std::string_view fen) {
  static const std::unordered_map<char, const char*> ch_to_img {
    { 'p', "bPawn.png" },
    { 'n', "bKnight.png" },
    { 'b', "bBishop.png" },
    { 'r', "bRook.png" },
    { 'q', "bQueen.png" },
    { 'k', "bKing.png" },

    { 'P', "wPawn.png" },
    { 'N', "wKnight.png" },
    { 'B', "wBishop.png" },
    { 'R', "wRook.png" },
    { 'Q', "wQueen.png" },
    { 'K', "wKing.png" }
  };

  // positions turn castling en-passant half-move full-move
  std::size_t positions = fen.find(' ');
  if(positions == std::string_view::npos)
    throw std::runtime_error("invalid FEN string. Failed to find space");

  for(std::size_t i = 0; i < positions; i++) {
    // TODO: Parse FEN. Only parse position & turn for now. The rest haven't been implemented yet.
  }
}

void Board::draw_pieces(SDL_Renderer *renderer) {
  for (std::size_t i = 0; i < m_pieces.size(); i++) {
    auto &piece = m_pieces[i];

    SDL_Point position{.x = Board::file(i) * Config::SQUARE_W,
                       .y = Board::rank(i) * Config::SQUARE_H};
    piece.draw(renderer, position);
  }
}

void Board::draw_board(SDL_Renderer *renderer) {

  SDL_FRect square_rect{.x = 0.f,
                        .y = 0.f,
                        .w = static_cast<float>(Config::SQUARE_W),
                        .h = static_cast<float>(Config::SQUARE_H)};

  SDL_Color color;

  for (int i = 0; i < (Config::DIM.x * Config::DIM.y); i++) {
    int file = Board::file(i);
    int rank = Board::rank(i);

    color = Config::COLORS[static_cast<std::size_t>((file + rank) % 2)];

    square_rect.x = static_cast<float>(file * Config::SQUARE_W);
    square_rect.y = static_cast<float>(rank * Config::SQUARE_H);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &square_rect);
  }
}
