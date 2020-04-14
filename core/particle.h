// Defines a base particle which contains the information necessary for
// rendering a particle in the simulator.

#ifndef AMOEBOTSIM_CORE_PARTICLE_H_
#define AMOEBOTSIM_CORE_PARTICLE_H_

#include <QString>

#include "core/node.h"

class Particle {
 public:
  // Constructs a new particle with a node position for its head and a global
  // compass direction from its head to its tail (-1 if contracted).
  Particle(const Node& head = Node(), int globalTailDir = -1);
  virtual ~Particle();

  // Functions for checking whether the particle is contracted or expanded.
  bool isContracted() const;
  bool isExpanded() const;

  // Functions to give color to the head and tail of particles. Colors set by
  // hex RGB values. Direction of head and tail markers are set by a direction
  // from 0 to 11.
  int virtual headMarkColor() const;
  int virtual tailMarkColor() const;
  int virtual globalHeadMarkDir() const;
  int virtual globalTailMarkDir() const;

  // Returns the string to be displayed when this particle is inspected; used
  // to snapshot the current values of this particle's memory at runtime.
  virtual QString inspectionText() const;

  // Returns the node occupied by the particle's tail. Returns the head node if
  // contracted, and otherwise returns the node in the global tail direction
  // from the head node.
  Node tail() const;

  Node head;
  int globalTailDir;
};

#endif  // AMOEBOTSIM_CORE_PARTICLE_H_
