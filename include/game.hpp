#pragma once

#include "board.hpp"

class Game {
public:
  Game();
  ~Game();

  void run();

private:
  void handle_events();
  void handle_mouse_input();

private:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;

  Board m_board;
  AssetManager m_manager;

  SDL_Event m_event;
  bool m_running;
};
