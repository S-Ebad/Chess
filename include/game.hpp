#pragma once

#include "board.hpp"

class Game {
public:
  Game();
  ~Game();

  void run();

private:
  void handle_events();

private:
  SDL_Window *m_window{};
  SDL_Renderer *m_renderer{};

  Board m_board;

  SDL_Event m_event;
  bool m_running;
};
