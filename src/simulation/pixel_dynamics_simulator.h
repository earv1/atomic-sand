#ifndef SRC_SIMULATION_PIXEL_DYNAMICS_SIMULATOR_H_
#define SRC_SIMULATION_PIXEL_DYNAMICS_SIMULATOR_H_

#include <SDL.h>

#include "../lib/simulation_structures.h"

struct Simulated_Particle** simulate_particles_one_step(
    int width,
    struct Simulated_Particle* simulated_particles_ptr);


void simulate_sand_particle(
    int width,
    int height,
    int x_coordinate,
    int y_coordinate,
    struct Simulated_Particle* simulated_particles
    ); 

void dump_particles_to_pixel_array(
    int width,
    int height,
    Uint32 * pixel_array,
    struct Simulated_Particle** simulated_particles
    ); 

#endif  // SRC_SIMULATION_PIXEL_DYNAMICS_SIMULATOR_H_

