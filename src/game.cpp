#include "game.hpp"
#include "settings.hpp"
#include <SDL3/SDL.h>
#include <format>
#include <iostream>
#include <stdexcept>

Game::Game()
    : m_window{nullptr}, m_renderer{nullptr}, m_manager{Config::IMAGES},
      m_event{}, m_running{false} {

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

  m_board.load_fen(m_manager, "rnbqkbnr/8/8/8/8/8/8/RNBQKBNR w KQkq - 0 1");
}

void Game::handle_mouse_input() {
  int x = m_event.button.x;
  int y = m_event.button.y;

  int row = static_cast<int>(y / Config::SQUARE_H);
  int col = static_cast<int>(x / Config::SQUARE_W);

  int square = Board::to_idx(row, col);

  legal_moves = MoveGenerator::generate_pseudo_legal_moves(m_board, square);

  std::cout << square << '\n';
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

void Game::draw_legal_moves() {
  SDL_FRect small_rect{.x = 0.f,
                       .y = 0.f,
                       .w = Config::SQUARE_W / 10.f,
                       .h = Config::SQUARE_H / 10.f};
  SDL_Color color{255, 0, 0, 255};
  for (const Move &move : legal_moves) {
    int file = Board::file(move.to);
    int rank = Board::rank(move.to);

    small_rect.x = static_cast<float>(file * Config::SQUARE_W);
    small_rect.y = static_cast<float>(rank * Config::SQUARE_H);

    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(m_renderer, &small_rect);
  }
}

void Game::run() {
  m_running = true;

  while (m_running) {
    handle_events();

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    Board::draw_board(m_renderer);
    m_board.draw_pieces(m_renderer);

    draw_legal_moves();

    SDL_RenderPresent(m_renderer);
  }
}

Game::~Game() {
  SDL_DestroyWindow(m_window);
  SDL_DestroyRenderer(m_renderer);

  SDL_Quit();
}
