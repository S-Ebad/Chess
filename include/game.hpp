#pragma once

#include "board.hpp"
#include "moves.hpp"

class Game {
public:
  Game();
  ~Game();

  void run();

private:
  void handle_events();
  void handle_mouse_input();

  void draw_legal_moves();

private:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;

  Board m_board;
  AssetManager m_manager;

  SDL_Event m_event;
  bool m_running;

  std::vector<Move> legal_moves;
};
