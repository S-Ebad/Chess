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
  SDL_Window *window{};
  SDL_Renderer *renderer{};

  Board board;

  SDL_Event event;
  bool running;
};
