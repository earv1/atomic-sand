// Copyright 2020-2030 Emmanuel Arvanitis

#include "pixel_dynamics_simulator.h"
#include "../lib/simulation_structures.h"
#include <stdbool.h>


#include <SDL.h>

  // struct Simulated_Particle** simulate_particles_one_step(
  //   int width,
  //   struct Simulated_Particle* simulated_particles
  //   ) {

  //   int x_search_space = sizeof(simulated_particles);

  //   if (x_search_space <= 0) {
  //     return simulated_particles;
  //   }

  //   int y_search_space = sizeof(simulated_particles);

  //   for (int x = 0; x < x_search_space; x++) {
  //     for (int y = 0; y < y_search_space; y++) {
  //       struct Simulated_Particle current_particle_to_simulate
  //         = simulated_particles[x + (y * width)];
  //     }
  //   }
  // }


  void dump_particles_to_pixel_array(
    int width,
    int height,
    Uint32 * pixel_array,
    struct Simulated_Particle ** simulated_particles
    ) {

      int x_search_space = width;
      int y_search_space = height;

      for (int x = 0; x < x_search_space; x++) {
        for (int y = 0; y < y_search_space; y++) {
          struct Simulated_Particle current_particle_to_display
            = *simulated_particles[x + (y * width)];
          pixel_array[x+(y * width)] = current_particle_to_display.rgb_value;
        }
      }
    }


