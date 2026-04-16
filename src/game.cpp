#include "game.hpp"
#include "settings.hpp"
#include <SDL3/SDL.h>
#include <format>
#include <stdexcept>

static const char *get_side_str(Side side) {
  switch (side) {
  case Side::White:
    return "White";
  case Side::Black:
    return "Black";
  case Side::None:
    return "Side_None";
  }
}

static const char *get_type_str(PieceType type) {
  switch (type) {
  case PieceType::King:
    return "King";
  case PieceType::Queen:
    return "Queen";
  case PieceType::Rook:
    return "Rook";
  case PieceType::Knight:
    return "Knight";
  case PieceType::Bishop:
    return "Bishop";
  case PieceType::Pawn:
    return "Pawn";
  case PieceType::None:
    return "Type_None";
  }
}

Game::Game()
    : m_window{nullptr}, m_renderer{nullptr}, m_manager{Config::IMAGES},
      m_board{}, m_event{}, m_running{false} {

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(
        std::format("ERROR: SDL_Init failed: {}", SDL_GetError()));
  }

  const int result =
      SDL_CreateWindowAndRenderer(Config::TITLE.data(), Config::WIDTH,
                                  Config::HEIGHT, 0, &m_window, &m_renderer);
  SDL_SetWindowResizable(m_window, false);

  if (!result) {
    throw std::runtime_error(std::format(
        "ERROR: SDL_CreateWindowAndRenderer failed: {}", SDL_GetError()));
  }

  // preload all assets
  for (const auto &[key, texture_path] : Config::PIECE_TEXTURES) {
    m_manager.load_asset(m_renderer, texture_path, key);
  }

  m_board.create_board_texture(m_renderer);
  m_board.load_fen(m_manager, Config::STARTING_POS);
}

void Game::handle_mouse_input() {
  size_t x = static_cast<size_t>(m_event.button.x / Config::SQUARE_W);
  size_t y = static_cast<size_t>(m_event.button.y / Config::SQUARE_H);

  Piece *selected = m_board.get_piece(Board::to_idx(y, x));

  if (selected)
    printf("Piece{ .side=%s, .type=%s }\n", get_side_str(selected->get_side()),
           get_type_str(selected->get_type()));
  else
    printf("Piece{ .side=%s, .type=%s }\n", get_side_str(Side::None),
           get_type_str(PieceType::None));
}

void Game::handle_events() {
  while (SDL_PollEvent(&m_event)) {
    switch (m_event.type) {
    case SDL_EVENT_QUIT:
      m_running = false;
      break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      handle_mouse_input();
      break;

    default:
      break;
    }
  }
}

void Game::run() {
  m_running = true;

  while (m_running) {
    handle_events();

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    m_board.draw_board(m_renderer);
    m_board.draw_pieces(m_renderer);

    SDL_RenderPresent(m_renderer);
    SDL_Delay(33);
  }
}

Game::~Game() {
  SDL_DestroyWindow(m_window);
  SDL_DestroyRenderer(m_renderer);

  SDL_Quit();
}
