// Copyright 2020-2030 Emmanuel Arvanitis
#include "game_loop.h"
#include <SDL.h>
#include <stdio.h>
#include  <signal.h>
#include  <stdlib.h>
#include "../lib/wiring.h"

#define TICK_INTERVAL    30

static Uint32 next_time;
void tick(struct AtomicSandWiring * wiring) {
     SDL_Renderer * renderer = wiring->renderer;
       printf("tick");
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      SDL_RenderDrawPoint(renderer, 1, 1);
      SDL_RenderPresent(renderer);
}

Uint32 time_left(void) {
    Uint32 now;

    now = SDL_GetTicks();
    if (next_time <= now)
      return 0;
    else
      return next_time - now;
  }

void game_loop(struct AtomicSandWiring * wiring) {
  /* main game loop */

  next_time = SDL_GetTicks() + TICK_INTERVAL;
  while (1) {
    tick(wiring);
    // update_game_state();
    SDL_Delay(time_left());
    next_time += TICK_INTERVAL;
  }
}