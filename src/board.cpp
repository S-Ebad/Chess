#include "board.hpp"
#include "settings.hpp"
#include <SDL3/SDL.h>
#include <format>

static std::pair<PieceType, Side> fen_to_piece(char c) {

  Side side = std::isupper(c) ? Side::White : Side::Black;

  switch (std::tolower(c)) {
  case 'r':
    return {PieceType::Rook, side};
  case 'n':
    return {PieceType::Knight, side};
  case 'b':
    return {PieceType::Bishop, side};
  case 'q':
    return {PieceType::Queen, side};
  case 'k':
    return {PieceType::King, side};
  case 'p':
    return {PieceType::Pawn, side};
  default:
    throw std::runtime_error("Invalid Piece");
  }
}

static void draw_board(SDL_Renderer *renderer) {

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

Board::Board() : m_pieces{} {}

void Board::create_board_texture(SDL_Renderer *renderer) {
  m_board_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                                           SDL_TEXTUREACCESS_TARGET,
                                           Config::WIDTH, Config::HEIGHT);

  SDL_SetRenderTarget(renderer, m_board_texture);
  ::draw_board(renderer);
  SDL_SetRenderTarget(renderer, nullptr);
}

void Board::load_fen(const AssetManager &manager, std::string_view fen) {
  std::size_t positions = fen.find(' ');
  if (positions == std::string_view::npos)
    throw std::runtime_error("invalid FEN string. Failed to find space");

  std::size_t j = 0;
  for (std::size_t i = 0; i < positions; i++) {
    const char c = fen[i];

    if (c == '/') {
      // each / should have dim.x (usually 8) squares
      if (j % (Config::DIM.x) != 0) {
        throw std::runtime_error(std::format(
            "malformed fen notation: goes beyond dimension (up to {})", j));
      }

      continue;
    }

    if (std::isdigit(c)) {
      j += static_cast<size_t>(c - '0');

      continue;
    }

    auto [type, side] = fen_to_piece(c);

    m_pieces[(size_t)j] = Piece{type, side, manager.get_asset(c)};

    j++;
  }

  switch (fen[positions + 1]) {
  case 'w':
    m_turn = Side::White;
    break;
  case 'b':
    m_turn = Side::Black;
    break;

  default:
    throw std::runtime_error(std::format(
        "malformed fen notation: Turn is invalid: {}", fen[positions + 1]));
  }
}

void Board::draw_pieces(SDL_Renderer *renderer) {
  for (std::size_t i = 0; i < m_pieces.size(); i++) {
    auto &piece = m_pieces[i];

    SDL_Point position{.x = Board::file((int)i) * Config::SQUARE_W,
                       .y = Board::rank((int)i) * Config::SQUARE_H};
    piece.draw(renderer, position);
  }
}

void Board::draw_board(SDL_Renderer *renderer) {
  SDL_FRect board_dims { .x=0.f, .y=0.f, .w=static_cast<float>(Config::WIDTH), .h=static_cast<float>(Config::HEIGHT) };

  SDL_RenderTexture(renderer, m_board_texture, nullptr, &board_dims);
}
