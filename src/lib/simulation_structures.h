// Copyright 2020-2030 Emmanuel Arvanitis

#ifndef SRC_LIB_SIMULATION_STRUCTURES_H_
#define SRC_LIB_SIMULATION_STRUCTURES_H_

struct Simulated_Particle_Wiring {
  int width;
  int height;
  struct Simulated_Particle* simulated_particles;
};

struct Simulated_Particle {
  int particle_id;
  int rgb_value;
  void (*Simulate_One_Step)(int width, int height, int x_coordinate,
                            int y_coordinate,
                            struct Simulated_Particle** simulated_particles);
};

#endif  // SRC_LIB_SIMULATION_STRUCTURES_H_
