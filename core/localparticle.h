#ifndef AMOEBOTSIM_CORE_LOCALPARTICLE_H
#define AMOEBOTSIM_CORE_LOCALPARTICLE_H

#include "core/node.h"
#include "core/particle.h"

class LocalParticle : public Particle {
 public:
  // Constructs a new particle with a node position for its head, a global
  // compass direction from its head to its tail (-1 if contracted), and an
  // orientation for its local compass.
  LocalParticle(const Node& head, int globalTailDir, const int orientation);

  // Returns the local direction of the tail relative to the head, (-1 if
  // contracted)
  int tailDir() const;

  // Functions for converting adjacent particle labels to local directions.
  // labelToDir returns the local direction the edge with the given label points
  // to. labelToDirAfterExpansion returns the local direction the particles with the
  // the given label would point to after an expansion in the given local
  // direction.
  int labelToDir(int label) const;
  int labelToDirAfterExpansion(int label, int expansionDir) const;

  // Functions for accessing labels specifically indicent to the head or tail.
  // headLabels (respectively, tailLabels) returns a vector of labels of
  // particles incident to the particle's head (respectively, tail). isHeadLabel
  // (resp., isTailLabel) checks whether the given label is a head (resp., tail)
  // label. dirToHeadLabel (resp., dirToTailLabel) returns the head (resp., tail)
  // label of the particle in the given local direction. These conversions will
  // fail on an expanded particle if dirToHeadLabel (resp., dirToTailLabel) is
  // called with the local direction from head to tail (resp., tail to head), as
  // the edge connecting the head and tail is not labelled.
  std::vector<int> headLabels() const;
  std::vector<int> tailLabels() const;
  bool isHeadLabel(int label) const;
  bool isTailLabel(int label) const;
  int dirToHeadLabel(int dir) const;
  int dirToTailLabel(int dir) const;

  // Functions analogous to their non -AfterExpansion versions above, but return
  // values as if the particle first expanded in the given local direction
  std::vector<int> headLabelsAfterExpansion(int expansionDir) const;
  std::vector<int> tailLabelsAfterExpansion(int expansionDir) const;
  bool isHeadLabelAfterExpansion(int label, int expansionDir) const;
  bool isTailLabelAfterExpansion(int label, int expansionDir) const;
  int dirToHeadLabelAfterExpansion(int dir, int expansionDir) const;
  int dirToTailLabelAfterExpansion(int dir, int expansionDir) const;

  // labelToGlobalDir returns the global direction the edge with the given label
  // points to. labelOfNbrNodeInGlobalDir returns the label of the particle that
  // connects the particle to given node (fails if the specified node is not in
  // the particle's neighborhood).
  int labelToGlobalDir(int label) const;
  int labelOfNbrNodeInGlobalDir(const Node& node, int globalDir) const;

  // occupiedNodeIncidentToLabel returns the head node if the given label is a
  // head label and the tail node otherwise. nbrNodeReachedViaLabel returns the
  // node reached from the particle by the edge with the given label.
  Node occupiedNodeIncidentToLabel(int label) const;
  Node nbrNodeReachedViaLabel(int label) const;

  // localToGlobalDir takes in a local direction and returns the corresponding
  // global direction. globalToLocalDir takes a global direction and returns
  // the local direction corresponding to that globalDir.
  int localToGlobalDir(int localDir) const;
  int globalToLocalDir(int globalDir) const;

  // Functions for converting between neighboring particles' local compasses.
  // nbrDirToDir returns the local direction from this particle's compass which
  // points in the same global direction as the given local direction from the
  // neighbor's compass. dirToNbrDir returns the local direction from the
  // neighbor's compass which points in the same global direction as the given
  // local direction from this particle's compass.
  int nbrDirToDir(const LocalParticle& nbr, int nbrDir) const;
  int dirToNbrDir(const LocalParticle& nbr, int myDir) const;

  // Functions for determining if a neighbor's label refers to an edge incident
  // to this particle. pointsAtMe checks if the labelled edge is incident
  // anywhere on this particle, whereas pointsAtMyHead (resp., pointsAtMyTail)
  // checks if the labelled edge is incident specifically to this particle's
  // head (resp., tail).
  bool pointsAtMe(const LocalParticle& nbr, int nbrLabel) const;
  bool pointsAtMyHead(const LocalParticle& nbr, int nbrLabel) const;
  bool pointsAtMyTail(const LocalParticle& nbr, int nbrLabel) const;

  // Orientation is an int in [0, 23] that represents a possible local compass
  // configuration. A particle can lie on one of four hexagonal layers,
  // have a cyclic rotation of 0, 2 or 4 and two different orthoginal up
  // local directions on that hexagonal layer.
  const int orientation;

  // labelMapping takes in a vector that represents the local compass
  // configuration of a particle after applying rotation and/or flip on the
  // L0 lattice then maps the compass configuration values to the correct
  // lattice based on the particle's orientation.
  std::vector<int> labelMapping(std::vector<int> basisVector) const;

  // Calculate opposite labels in contracted and expanded particles,
  int oppositeLabel(int label) const;

  // Function to calculate opposite directions.
  int oppositeDir(int dir) const;

  // Function to map expansionDirections in L0 to the correct local expansion
  // in its local compass configurations.
  int mappedExpansion(int expandDir) const;

  // Function to map a label in L0 to the correct local local
  // in its local compass configurations.
  int mappedLabel(int label) const;

  // Function to map a local dir in L0 to the correct local dir
  // in its local compass configurations.
  int mappedDir(int dir) const;

  // Functions to calculate the labels adjacent to the head of expanded
  // particles. sharedLabels takes in the labels adjacent to the head of an
  // expanded particle and returns the labels shared by both the head and tail
  // of the expanded particle. adjacentLables takes in a vector of labels
  // adjacent to the head in the same hexagonal plane and returns all the
  // labels above, below and in that hexagonal plane. surroundLabels is a
  // helper function to return all adjacent and shared labels of the head
  // of an expanded particle.
  std::vector<int> sharedLabels(std::vector<int> labels) const;
  std::vector<int> adjacentLabels(std::vector<int> labels) const;
  std::vector<int> surroundLabels(std::vector<int> adjacentLabels) const;

 private:
  // latticeDir is a set of vectors that represents the different rotation &
  // flip combinations within the same hexagonal plane. Vectors in index 0-2
  // represents a cyclic rotation of 0, 2, and 4 with no flip & index 3-5
  // represents a cyclic rotation of 0, 2, and 4 with a flip.
  static const std::vector<std::vector<int>> latticeDir;

  // latticeMappings is a strucutre used to convert different lattice
  // configurations to correct global orientation. The first set of vectors
  // represents the conversions for the four different hexagonal planes
  // of contracted particles and the second set of vectors represents the
  // conversions between the four hexagnal planes of expanded particles.
  static const std::vector<std::vector<std::vector<int>>> latticeMappings;

  // expandLabel represents the local labeling of a particle after expanding
  // in directions i in [0,12]. Vector at i represents the its labeling scheme
  // after expanding in direction i.
  static const std::vector<std::vector<int>> expandLabel;

  // expandDir maps the repsective expandLabel labels to local directions.
  static const std::vector<std::vector<int>> expandDir;

};
#endif // AMOEBOTSIM_CORE_LOCALPARTICLE_H
