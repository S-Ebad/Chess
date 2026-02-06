#pragma once

#include "SDL3/SDL.h"

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

  SDL_Event event;
  bool running;
};
