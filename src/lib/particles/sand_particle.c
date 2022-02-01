#include "../simulation_structures.h"
#include <stdbool.h>
#include "sand_particle.h"

#include "./null_particle.h"


int sand_particle_id = SAND_PARTICLE_ID;

void Simulate_One_Step_Sand(int width, int height, int x_coordinate,
                       int y_coordinate,
                       struct Simulated_Particle** simulated_particles_ptr) {


  struct Simulated_Particle current_particle_to_simulate =
      *simulated_particles_ptr[x_coordinate + y_coordinate * width];

  if (y_coordinate >= height) {
    return;
  }

  struct Simulated_Particle lower_middle_particle =
      *simulated_particles_ptr[x_coordinate + (y_coordinate + 1) * width];

  if (y_coordinate < height - 2 &&
      current_particle_to_simulate.particle_id == sand_particle_id) {
    // struct Simulated_Particle empty_particle = {};
    // struct Simulated_Particle sand_particle = {};

    struct Simulated_Particle *sand_particle = Sand_Particle_Init();
    struct Simulated_Particle *null_particle = Null_Particle_Init();

    // Fall
    if (lower_middle_particle.particle_id == null_particle->particle_id) {
      // printf("simulate %d,%d \n", x_coordinate, y_coordinate);

      simulated_particles_ptr[x_coordinate + (y_coordinate + 1) * (width)] =
          sand_particle;
      simulated_particles_ptr[x_coordinate + y_coordinate * width] = null_particle;
      // current_particle_to_simulate = empty_simulated_particle;
    } else {
      int leftRightRandomInt = rand() % 2;

      if (leftRightRandomInt == 0) {
        leftRightRandomInt = -1;
      }

      struct Simulated_Particle lower_left_right_random_particle =
          *simulated_particles_ptr[x_coordinate + leftRightRandomInt +
                              (y_coordinate + 1) * width];

      bool leftBoundaryReached = !(x_coordinate > 0);
      bool rightBoundaryReached = !(x_coordinate < width);

      bool boundaryReached =
          (leftRightRandomInt == -1 && leftBoundaryReached) ||
          (leftRightRandomInt == 1 && rightBoundaryReached);

      if (!boundaryReached && lower_left_right_random_particle.particle_id ==
                                  null_particle->particle_id) {
        simulated_particles_ptr[x_coordinate + leftRightRandomInt +
                            (y_coordinate + 1) * (width)] = sand_particle;
        simulated_particles_ptr[x_coordinate + y_coordinate * width] =
            null_particle;
      }

    }
  }
}

struct Simulated_Particle sand_particle;
struct Simulated_Particle *Sand_Particle_Init() {
  sand_particle.particle_id = sand_particle_id;
  sand_particle.rgb_value = 0xFFCC00;
  sand_particle.Simulate_One_Step = &Simulate_One_Step_Sand;

  return &sand_particle;
}
