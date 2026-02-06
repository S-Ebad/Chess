#include "game.hpp"
#include "settings.hpp"
#include <SDL3/SDL.h>
#include <format>
#include <stdexcept>

Game::Game() : event{}, running {false} {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(
        std::format("ERROR: SDL_Init failed: {}", SDL_GetError()));
  }

  const int result = SDL_CreateWindowAndRenderer(Config::TITLE.data(), Config::WIDTH, Config::HEIGHT, 0, &this->window,
                                           &this->renderer);

  if (!result) {
    throw std::runtime_error(std::format(
        "ERROR: SDL_CreateWindowAndRenderer failed: {}", SDL_GetError()));
  }
}

void Game::handle_events() {
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      running = false;
      break;

    default:
      break;
    }
  }
}

void Game::run() {
  this->running = true;

  while (running) {
    this->handle_events();

    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);

    Board::draw_board(renderer);

    SDL_RenderPresent(this->renderer);
  }
}

Game::~Game() {
  SDL_DestroyWindow(this->window);
  SDL_DestroyRenderer(this->renderer);

  SDL_Quit();
}
