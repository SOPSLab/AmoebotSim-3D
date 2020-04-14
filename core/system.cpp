#include "core/system.h"

System::System() {
  for (uint i = 0; i < 11; ++i) {
    _particles.push_back(Particle(Node(0, 0, 0).nodeInDir(i), -1));
  }
  _particles.push_back(Particle(Node(0, 0, 0).nodeInDir(11), 5));
}

std::vector<Particle> System::getParticles() {
  return _particles;
}
