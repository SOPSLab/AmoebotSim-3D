// Defines a base particle system serving the purpose of defining functions to
// be overridden by subclasses.

#ifndef AMOEBOTSIM_CORE_SYSTEM_H_
#define AMOEBOTSIM_CORE_SYSTEM_H_

#include <vector>

#include "core/particle.h"

class System {
 public:
  // Default constructor (currently fills the particle list with dummy particles
  // but will be changed in the future).
  System();

  std::vector<Particle> getParticles();

 private:
  std::vector<Particle> _particles;
};

#endif  // AMOEBOTSIM_CORE_SYSTEM_H_
