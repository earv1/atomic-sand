// Copyright 2020-2030 Emmanuel Arvanitis
#include "game_loop.h"

#include <SDL.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "../lib/simulation_structures.h"
#include "../lib/state.h"
#include "../lib/wiring.h"
#include "../simulation/pixel_dynamics_simulator.h"
#include "../lib/particles/sand_particle.h"
#include "../lib/particles/null_particle.h"

#define TICK_INTERVAL 30

#define WIN_WIDTH 160
#define WIN_HEIGHT 144

// Render pixels
// https://gist.github.com/superzazu/f24aaf202248440c6097b85105d0bbae
// https://gigi.nullneuron.net/gigilabs/sdl2-pixel-drawing/

static Uint32 next_time;

void render_pixel_array(Uint32 *pixelArray, SDL_Texture *texture,
                        SDL_Renderer *renderer) {
  int texture_pitch = 0;
  void *texture_pixels = NULL;
  if (SDL_LockTexture(texture, NULL, &texture_pixels, &texture_pitch) != 0) {
    SDL_Log("Unable to lock texture: %s", SDL_GetError());
  } else {
    memcpy(texture_pixels, pixelArray, texture_pitch * WIN_HEIGHT);
  }
  SDL_UnlockTexture(texture);
  // SDL_UpdateTexture(texture, NULL, pixelArray, WIN_HEIGHT * sizeof(Uint32));
  // render on screen
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void tick(struct AtomicSandWiring *wiring, struct Game_State *game_state) {
  Uint32 pixels[WIN_WIDTH * WIN_HEIGHT] = {0};

  // memset(pixels, 255, WIN_WIDTH * WIN_HEIGHT * sizeof(Uint32));

  // for (int x = 0; x < WIN_WIDTH * WIN_HEIGHT; x++) {
  //   pixels[x] = 0xFFFFFF;
  // }
  // for (int x = 0; x < WIN_WIDTH*30; x++) {
  //   if (x%2 == 0) {
  //     pixels[x] = 0xFF3000;
  //   } else {
  //     pixels[x] = NULL;
  //   }
  // }

  // TODO(Emmanuel) change to bottom first search
  for (int x = 0; x < WIN_WIDTH; x++) {
    for (int y = WIN_HEIGHT -1; y >= 0; y--) {

      int current_index = x + (y * WIN_WIDTH);
      struct Simulated_Particle *current_particle_to_simulate =
        game_state->simulated_particles[current_index];

      // int simulation_function = 
      //   (*current_particle_to_simulate).Simulate_One_Step;
      (*current_particle_to_simulate).Simulate_One_Step(
          WIN_WIDTH, WIN_HEIGHT, x, y, game_state->simulated_particles);
    }
  }

  dump_particles_to_pixel_array(WIN_WIDTH, WIN_HEIGHT, pixels,
                                game_state->simulated_particles);

  render_pixel_array(pixels, wiring->texture, wiring->renderer);
}

Uint32 time_left(void) {
  Uint32 now;

  now = SDL_GetTicks();
  if (next_time <= now)
    return 0;
  else
    return next_time - now;
}

void game_loop(struct AtomicSandWiring *wiring) {
  /* main game loop */
  next_time = SDL_GetTicks() + TICK_INTERVAL;

  struct Simulated_Particle *sand_particle = Sand_Particle_Init();
  struct Simulated_Particle *null_particle = Null_Particle_Init();
  // sand_particle.particle_type =
  //     PARTICLE_TYPE_SAND;

  struct Game_State game_state;

  struct Simulated_Particle *simulated_particle_array[WIN_WIDTH * WIN_HEIGHT];
  for (int x = 0; x < (WIN_WIDTH * WIN_HEIGHT); x++) {
    simulated_particle_array[x] = null_particle;
  }

  simulated_particle_array[0] = sand_particle;
  // simulated_particle_array[160] = sand_particle;
  int randomNum = 0;
  unsigned int seed = 24;
  while (1) {
    randomNum = rand_r(&seed) % 3;
    if (randomNum == 1) {
      simulated_particle_array[0] = sand_particle;
      simulated_particle_array[WIN_WIDTH -1] = sand_particle;
    } else if (randomNum == 2) {
      simulated_particle_array[WIN_WIDTH * 2 + WIN_WIDTH / 2] = sand_particle;
      simulated_particle_array[WIN_WIDTH * 2 + WIN_WIDTH / 4] = sand_particle;
      simulated_particle_array[WIN_WIDTH * 2 + (WIN_WIDTH / 4) * 3] =
          sand_particle;
    }


  game_state.simulated_particles = simulated_particle_array;
    tick(wiring, &game_state);
    // update_game_state();
    // SDL_Delay(time_left());
    // char c = getchar();
    usleep(100);

    next_time += TICK_INTERVAL;
  }
}
