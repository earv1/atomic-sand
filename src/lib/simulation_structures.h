// Copyright 2020-2030 Emmanuel Arvanitis

#ifndef SRC_LIB_SIMULATION_STRUCTURES_H_
#define SRC_LIB_SIMULATION_STRUCTURES_H_

  enum PARTICLE_TYPES {
    PARTICLE_TYPE_EMPTY = 0,
    PARTICLE_TYPE_SAND = 1
  };
  typedef enum PARTICLE_TYPES PARTICLE_TYPES;

  struct Simulated_Particle {
    PARTICLE_TYPES particle_type;
  };


#endif  // SRC_LIB_SIMULATION_STRUCTURES_H_
