#include "../simulation_structures.h"
#include <stdbool.h>
#include "null_particle.h"


void Simulate_One_Step_Null(int width, int height, int x_coordinate,
                       int y_coordinate,
                       struct Simulated_Particle** simulated_particles) {
    // printf("simulate null\n");
}

struct Simulated_Particle null_particle;
struct Simulated_Particle *Null_Particle_Init() {
  null_particle.particle_id = NULL_PARTICLE_ID;
  null_particle.rgb_value = 0x6a0dad;
  null_particle.Simulate_One_Step = &Simulate_One_Step_Null;
  return &null_particle;
}
