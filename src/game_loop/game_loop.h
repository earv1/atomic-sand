// Copyright 2020-2030 Emmanuel Arvanitis

#ifndef SRC_GAME_LOOP_GAME_LOOP_H_
#define SRC_GAME_LOOP_GAME_LOOP_H_

#include <SDL.h>
#include <stdio.h>
#include  <signal.h>
#include  <stdlib.h>
#include "../lib/wiring.h"
#include "../lib/state.h"

void tick(struct AtomicSandWiring *wiring, struct Game_State *game_state);

Uint32 time_left(void);

void game_loop(struct AtomicSandWiring * wiring);

static void render_pixel_array(
    Uint32 * pixelArray,
    SDL_Texture * texture,
    SDL_Renderer * renderer);

#endif  // SRC_GAME_LOOP_GAME_LOOP_H_
