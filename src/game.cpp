#include "game.hpp"
#include "settings.hpp"
#include <SDL3/SDL.h>
#include <format>
#include <stdexcept>

Game::Game() : m_event{}, m_running{false} {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(
        std::format("ERROR: SDL_Init failed: {}", SDL_GetError()));
  }

  const int result =
      SDL_CreateWindowAndRenderer(Config::TITLE.data(), Config::WIDTH,
                                  Config::HEIGHT, 0, &m_window, &m_renderer);

  if (!result) {
    throw std::runtime_error(std::format(
        "ERROR: SDL_CreateWindowAndRenderer failed: {}", SDL_GetError()));
  }
}

void Game::handle_events() {
  while (SDL_PollEvent(&m_event)) {
    switch (m_event.type) {
    case SDL_EVENT_QUIT:
      m_running = false;
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

    Board::draw_board(m_renderer);

    SDL_RenderPresent(m_renderer);
  }
}

Game::~Game() {
  SDL_DestroyWindow(m_window);
  SDL_DestroyRenderer(m_renderer);

  SDL_Quit();
}
