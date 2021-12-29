// Copyright 2020-2030 Emmanuel Arvanitis

#ifndef SRC_GAME_LOOP_GAME_LOOP_H_
#define SRC_GAME_LOOP_GAME_LOOP_H_

#include <SDL.h>
#include <stdio.h>
#include  <signal.h>
#include  <stdlib.h>
#include "../lib/wiring.h"

void tick(struct AtomicSandWiring * wiring);

Uint32 time_left(void);

void game_loop(struct AtomicSandWiring * wiring);

#endif  // SRC_GAME_LOOP_GAME_LOOP_H_
