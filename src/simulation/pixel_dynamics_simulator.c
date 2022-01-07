// Copyright 2020-2030 Emmanuel Arvanitis

#include "pixel_dynamics_simulator.h"
#include "../lib/simulation_structures.h"
#include <stdbool.h>


#include <SDL.h>

    int retrieve_rgb_for_particle(enum PARTICLE_TYPES particle_type) {
      switch (particle_type) {
        case PARTICLE_TYPE_SAND:
          return 0xFFCC00;
          break;
        default:
          return 0x6a0dad;
      }
    }

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

    void simulate_sand_particle(
        int width, int height, int x_coordinate, int y_coordinate,
        struct Simulated_Particle* simulated_particles) {
      struct Simulated_Particle current_particle_to_simulate =
          simulated_particles[x_coordinate + y_coordinate * width];

      if (y_coordinate >= height) {
        return;
      }

      struct Simulated_Particle lower_middle_particle =
          simulated_particles[x_coordinate + (y_coordinate + 1) * width];

      struct Simulated_Particle lower_left_particle =
          simulated_particles[x_coordinate - 1 + (y_coordinate + 1) * width];

      struct Simulated_Particle lower_right_particle =
          simulated_particles[x_coordinate + 1 + (y_coordinate + 1) * width];

      if (y_coordinate < height - 1 &&
          current_particle_to_simulate.particle_type == PARTICLE_TYPE_SAND) {
        struct Simulated_Particle empty_particle = {};
        struct Simulated_Particle sand_particle = {};
        sand_particle.particle_type = PARTICLE_TYPE_SAND;

        // Fall
        if (lower_middle_particle.particle_type == PARTICLE_TYPE_EMPTY) {
          // printf("simulate %d,%d \n", x_coordinate, y_coordinate);

          simulated_particles[x_coordinate + (y_coordinate + 1) * (width)] =
              sand_particle;
          simulated_particles[x_coordinate + y_coordinate * width] =
              empty_particle;
          // current_particle_to_simulate = empty_simulated_particle;
        } else {
          int leftRightRandomInt = rand() % 2;

          if (leftRightRandomInt == 0) {
            leftRightRandomInt = -1;
          }

          struct Simulated_Particle lower_left_right_random_particle =
              simulated_particles[x_coordinate + leftRightRandomInt +
                                  (y_coordinate + 1) * width];

          bool leftBoundaryReached = !(x_coordinate > 0);
          bool rightBoundaryReached = !(x_coordinate < width);

          bool boundaryReached =
              (leftRightRandomInt == -1 && leftBoundaryReached) ||
              (leftRightRandomInt == 1 && rightBoundaryReached);

          if (!boundaryReached &&
              lower_left_right_random_particle.particle_type ==
                  PARTICLE_TYPE_EMPTY) {
            simulated_particles[x_coordinate + leftRightRandomInt +
                                (y_coordinate + 1) * (width)] = sand_particle;
            simulated_particles[x_coordinate + y_coordinate * width] =
                empty_particle;
          }
        }
      }
    }

  void dump_particles_to_pixel_array(
    int width,
    int height,
    Uint32 * pixel_array,
    struct Simulated_Particle * simulated_particles
    ) {

      int x_search_space = width;

      int y_search_space = height;


      for (int x = 0; x < x_search_space; x++) {
        for (int y = 0; y < y_search_space; y++) {

          struct Simulated_Particle current_particle_to_display
            = simulated_particles[x + (y * width)];
          int particle_type = current_particle_to_display.particle_type;
          pixel_array[x+(y * width)] = retrieve_rgb_for_particle(particle_type);
        }
      }
    }


