#include "core/localparticle.h"
#include "helper/conversion.h"

const std::vector<std::vector<int>> LocalParticle::latticeDir = {
  {
     {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
     {4, 5, 0, 1, 2, 3, 8, 6, 7, 11, 9, 10},
     {2, 3, 4, 5, 0, 1, 7, 8, 6, 10, 11, 9},
     {0, 5, 4, 3, 2, 1, 11, 10, 9, 8, 7, 6},
     {2, 1, 0, 5, 4, 3, 9, 11, 10, 6, 8, 7},
     {4, 3, 2, 1, 0, 5, 10, 9, 11, 7, 6, 8}
  }
};

const std::vector<std::vector<std::vector<int>>> LocalParticle::latticeMappings
= {
  {
    {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
    {1, 9, 10, 4, 8, 6, 2, 3, 7, 11, 5, 0},
    {3, 7, 6, 0, 11, 10, 2, 1, 9, 8, 4, 5},
    {9, 2, 7, 8, 5, 11, 1, 6, 0, 3, 4, 10}
    },

    {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17},
    {14, 15, 5, 11, 9, 2, 13, 16, 6, 12, 8, 1, 3, 4, 10, 17, 7, 0},
    {4, 10, 9, 8, 0, 17, 16, 15, 3, 2, 1, 13, 14, 11, 12, 7, 6, 5},
    {17, 13, 2, 9, 12, 7, 16, 14, 3, 10, 11, 6, 0, 1, 8, 4, 5, 15}
    }
  }
};

const std::vector<std::vector<int>> LocalParticle::expandLabel = {
  {
     {6, 7, 0, 1, 2, 3, 4, 5, 12, 8, 9, 10, 11, 17, 13, 14, 15, 16},
     {7, 0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 17, 13, 14, 15, 16},
     {1, 2, 3, 4, 5, 6, 7, 0, 9, 10, 11, 12, 8, 14, 15, 16, 17, 13},
     {2, 3, 4, 5, 6, 7, 0, 1, 10, 11, 12, 8, 9, 14, 15, 16, 17, 13},
     {3, 4, 5, 6, 7, 0, 1, 2, 10, 11, 12, 8, 9, 15, 16, 17, 13, 14},
     {5, 6, 7, 0, 1, 2, 3, 4, 12, 8, 9, 10, 11, 16, 17, 13, 14, 15},
     {4, 5, 0, 1, 2, 3, 10, 11, 6, 7, 8, 9, 14, 12, 13, 17, 15, 16},
     {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17},
     {2, 3, 4, 5, 0, 1, 8, 9, 10, 11, 6, 7, 13, 14, 12, 16, 17, 15},
     {6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 12, 13, 14, 15, 16, 17},
     {9, 10, 11, 6, 7, 8, 3, 4, 5, 0, 1, 2, 14, 12, 13, 16, 17, 15},
     {11, 6, 7, 8, 9, 10, 5, 0, 1, 2, 3, 4, 12, 13, 14, 15, 16, 17}
   }
};
const std::vector<std::vector<int>> LocalParticle::expandDir = {
  {
     {4, 5, 0, 1, 2, 2, 3, 4, 8, 6, 7, 7, 8, 11, 9, 9, 10, 10},
     {5, 0, 1, 2, 3, 3, 4, 5, 6, 7, 7, 8, 8, 11, 9, 10, 10, 11},
     {0, 1, 2, 3, 4, 4, 5, 0, 6, 7, 8, 8, 6, 9, 10, 10, 11, 11},
     {1, 2, 3, 4, 5, 5, 0, 1, 7, 8, 8, 6, 6, 9, 10, 11, 11, 9},
     {2, 3, 4, 5, 0, 0, 1, 2, 7, 8, 6, 6, 7, 10, 11, 11, 9, 9},
     {3, 4, 5, 0, 1, 1, 2, 3, 8, 6, 6, 7, 7, 10, 11, 9, 9, 10},
     {4, 5, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 8, 6, 7, 11, 9, 10},
     {0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
     {2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 0, 1, 7, 8, 6, 10, 11, 9},
     {0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 9, 10, 11, 6, 7, 8},
     {3, 4, 5, 0, 1, 2, 3, 4, 5, 0, 1, 2, 10, 11, 9, 8, 6, 7},
     {5, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 11, 9, 10, 6, 7, 8}
   }
};

LocalParticle::LocalParticle(const Node& head, int globalTailDir,
                             const int orientation)
  : Particle(head, globalTailDir),
  orientation(orientation) {
  Q_ASSERT(0 <= orientation && orientation < 12);
}

int LocalParticle::tailDir() const {
  Q_ASSERT(-1 <= globalTailDir && globalTailDir < 12);

  return isContracted() ? -1 : globalToLocalDir(globalTailDir);
}

int LocalParticle::labelToDir(int label) const {
  Q_ASSERT(-1 <= globalTailDir && globalTailDir < 12);
  if (isContracted()) {
    Q_ASSERT(0 <= label && label < 12);
    return label;
  } else {
    Q_ASSERT(0 <= label && label < 18);
    return labelMapping(
          expandDir[Conversion::intToUInt(oppositeDir(globalTailDir))])
                   [Conversion::intToUInt(mappedLabel(label))];
  }
}

int LocalParticle::labelToDirAfterExpansion(int label, int expansionDir) const {
  Q_ASSERT(isContracted());
  Q_ASSERT(0 <= label && label < 12);
  Q_ASSERT(0 <= expansionDir && expansionDir < 12);

  return labelMapping(
        expandDir[Conversion::intToUInt(mappedExpansion(expansionDir))])
                 [Conversion::intToUInt(mappedLabel(label))];
}


std::vector<int> LocalParticle::headLabels() const {
  Q_ASSERT(-1 <= globalTailDir && globalTailDir < 11);
  if (isContracted()) {
    return labelMapping(latticeDir[Conversion::intToUInt(orientation % 6)]);
  } else {
    std::vector<int> localLabels
        = expandLabel[Conversion::intToUInt(oppositeDir(globalTailDir))];
    std::vector<int> head (localLabels.begin(), localLabels.begin() + 5);
    return labelMapping(surroundLabels(head));
  }
}

std::vector<int> LocalParticle::tailLabels() const {
  Q_ASSERT(!isContracted());
  std::vector<int> tail;
  std::vector<int> shared;
  std::vector<int> localLabels
      = expandLabel[Conversion::intToUInt(oppositeDir(globalTailDir))];
  std::vector<int> head (localLabels.begin(), localLabels.begin() + 5);
  head = adjacentLabels(head);
  shared = sharedLabels(head);
  for (int i = 0; i < 18; ++i) {
    if (std::find(head.begin(), head.end(), i) == head.end()) {
      tail.push_back(i);
    }
  }
  tail.insert(tail.end(), shared.begin(), shared.end());
  return labelMapping(tail);
}

bool LocalParticle::isHeadLabel(int label) const {
  Q_ASSERT(0 <= label && label < 18);
  for (const int headLabel : headLabels()) {
    if (label == headLabel) {
      return true;
    }
  }
  return false;
}

bool LocalParticle::isTailLabel(int label) const {
  Q_ASSERT(isExpanded());
  Q_ASSERT(0 <= label && label < 18);
  for (const int tailLabel : tailLabels()) {
    if (label == tailLabel) {
      return true;
    }
  }
  return false;
}

int LocalParticle::dirToHeadLabel(int dir) const {
  Q_ASSERT(0 <= dir && dir < 12);
  for (const int headLabel : headLabels()) {
    if (dir == labelToDir(headLabel)) {
      return headLabel;
    }
  }
  Q_ASSERT(false);
  return 0;  // Avoid compiler warning.
}


int LocalParticle::dirToTailLabel(int dir) const {
  Q_ASSERT(isExpanded());
  Q_ASSERT(0 <= dir && dir < 12);
  for (const int tailLabel : tailLabels()) {
    if (dir == labelToDir(tailLabel)) {
      return tailLabel;
    }
  }
  Q_ASSERT(false);
  return 0;  // Avoid compiler warning.
}

std::vector<int> LocalParticle::headLabelsAfterExpansion(int expansionDir)
const {
  Q_ASSERT(isContracted());
  Q_ASSERT(0 <= expansionDir && expansionDir < 12);
  std::vector<int> localLabels
      = expandLabel[Conversion::intToUInt(mappedExpansion(expansionDir))];
  std::vector<int> head (localLabels.begin(), localLabels.begin() + 5);
  return labelMapping(surroundLabels(head));
}


std::vector<int> LocalParticle::tailLabelsAfterExpansion(int expansionDir)
const {
  Q_ASSERT(isContracted());
  Q_ASSERT(0 <= expansionDir && expansionDir < 12);
  std::vector<int> tail;
  std::vector<int> shared;
  std::vector<int> localLabels
      = expandLabel[Conversion::intToUInt(mappedExpansion(expansionDir))];
  std::vector<int> head (localLabels.begin(), localLabels.begin() + 5);
  head = adjacentLabels(head);
  shared = sharedLabels(head);
  for (int i = 0; i < 18; ++i) {
    if (std::find(head.begin(), head.end(), i) == head.end()) {
      tail.push_back(i);
    }
  }
  tail.insert(tail.end(), shared.begin(), shared.end());
  return labelMapping(tail);
}

bool LocalParticle::isHeadLabelAfterExpansion(int label, int expansionDir)
const {
  Q_ASSERT(isContracted());
  Q_ASSERT(0 <= expansionDir && expansionDir < 12);
  for (const int headLabel : headLabelsAfterExpansion(expansionDir)) {
    if (label == headLabel) {
      return true;
    }
  }
  return false;
}

bool LocalParticle::isTailLabelAfterExpansion(int label, int expansionDir)
const {
  Q_ASSERT(isContracted());
  Q_ASSERT(0 <= expansionDir && expansionDir < 12);
  for (const int tailLabel : tailLabelsAfterExpansion(expansionDir)) {
    if (label == tailLabel) {
      return true;
    }
  }
  return false;
}

int LocalParticle::dirToHeadLabelAfterExpansion(int dir, int expansionDir)
const {
  Q_ASSERT(isContracted());
  Q_ASSERT(0 <= dir && dir < 12);
  Q_ASSERT(0 <= expansionDir && expansionDir < 12);
  for (const int headLabel : headLabelsAfterExpansion(expansionDir)) {
    if (dir == labelToDirAfterExpansion(headLabel, expansionDir)) {
      return headLabel;
    }
  }
  Q_ASSERT(false);
  return 0;  // Avoid compiler warning.
}

int LocalParticle::dirToTailLabelAfterExpansion(int dir, int expansionDir)
const {
  Q_ASSERT(isContracted());
  Q_ASSERT(0 <= dir && dir < 12);
  Q_ASSERT(0 <= expansionDir && expansionDir < 12);
  for (const int tailLabel : tailLabelsAfterExpansion(expansionDir)) {
    if (dir == labelToDirAfterExpansion(tailLabel, expansionDir)) {
      return tailLabel;
    }
  }
  Q_ASSERT(false);
  return 0;  // Avoid compiler warning.
}

int LocalParticle::labelToGlobalDir(int label) const {
  Q_ASSERT(0 <= label && label < 18);
  return localToGlobalDir(labelToDir(label));
}

int LocalParticle::labelOfNbrNodeInGlobalDir(const Node& node, int globalDir)
const {
  Q_ASSERT(0 <= globalDir && globalDir < 12);
  const int labelLimit = (isContracted()) ? 12 : 18;
  for (int label = 0; label < labelLimit; label++) {
    if (labelToGlobalDir(label) == globalDir &&
        nbrNodeReachedViaLabel(label) == node) {
      return label;
    }
  }
  Q_ASSERT(false);
  return 0;  // Avoid compiler warning.
}

Node LocalParticle::occupiedNodeIncidentToLabel(int label) const {
  Q_ASSERT(-1 <= globalTailDir && globalTailDir < 6);
  if (isContracted()) {
    Q_ASSERT(0 <= label && label < 12);
    return head;
  } else {
    Q_ASSERT(0 <= label && label < 18);
    return isHeadLabel(label) ? head : tail();
  }
}

Node LocalParticle::nbrNodeReachedViaLabel(int label) const {
  Q_ASSERT(-1 <= globalTailDir && globalTailDir < 12);
  if (isContracted()) {
    Q_ASSERT(0 <= label && label < 12);
    return head.nodeInDir(Conversion::intToUInt(labelToGlobalDir(label)));
  } else {
    Q_ASSERT(0 <= label && label < 18);
    Node incidentNode = occupiedNodeIncidentToLabel(label);
    return incidentNode.nodeInDir(
                        Conversion::intToUInt(labelToGlobalDir(label)));
  }
}

int LocalParticle::localToGlobalDir(int localDir) const {
  Q_ASSERT(0 <= localDir && localDir < 12);
  return latticeDir[Conversion::intToUInt(orientation % 6)]
                   [Conversion::intToUInt(mappedDir(localDir))];
}

int LocalParticle::globalToLocalDir(int globalDir) const {
  return labelMapping(latticeDir[Conversion::intToUInt(orientation % 6)])
                     [Conversion::intToUInt(globalDir)];
}

int LocalParticle::nbrDirToDir(const LocalParticle& nbr, int nbrDir) const {
  Q_ASSERT(0 <= nbrDir && nbrDir < 12);
  return globalToLocalDir(nbr.localToGlobalDir(nbrDir));
}

int LocalParticle::dirToNbrDir(const LocalParticle& nbr, int myDir) const {
  Q_ASSERT(0 <= myDir && myDir < 12);
  return nbr.globalToLocalDir(localToGlobalDir(myDir));
}

bool LocalParticle::pointsAtMe(const LocalParticle& nbr, int nbrLabel) const {
  Q_ASSERT(0 <= nbrLabel && nbrLabel < 18);
  if (isContracted()) {
    return pointsAtMyHead(nbr, nbrLabel);
  } else {
    return pointsAtMyHead(nbr, nbrLabel) || pointsAtMyTail(nbr, nbrLabel);
  }
}

bool LocalParticle::pointsAtMyHead(const LocalParticle& nbr, int nbrLabel)
const {
  Q_ASSERT(0 <= nbrLabel && nbrLabel < 18);
  return nbr.nbrNodeReachedViaLabel(nbrLabel) == head;
}

bool LocalParticle::pointsAtMyTail(const LocalParticle& nbr, int nbrLabel)
const {
  Q_ASSERT(isExpanded());
  Q_ASSERT(0 <= nbrLabel && nbrLabel < 18);
  return nbr.nbrNodeReachedViaLabel(nbrLabel) == tail();
}


std::vector<int> LocalParticle::labelMapping(std::vector<int> basisVector)
const {
  std::vector<int> labelingScheme;
  int conversionOption
    = *max_element(std::begin(basisVector), std::end(basisVector)) > 12 ? 1 : 0;
  for (int i: basisVector) {
    labelingScheme.push_back(
          latticeMappings[Conversion::intToUInt(conversionOption)]
                         [Conversion::intToUInt(orientation / 6)]
                         [Conversion::intToUInt(i)]);
  }
  return labelingScheme;
}

int LocalParticle::oppositeLabel(int label) const {
  if (isContracted()) {
    return oppositeDir(label);
  } else {
    if (globalTailDir < 6) {
      int opp[] {4, 5, 6, 7, 0, 1, 2, 3, 15, 16, 17, 13, 14, 11, 12, 8, 9, 10};
      return opp[label];
    } else {
      int opp[] {3, 4, 5, 0, 1, 2, 9, 10, 11, 6, 7, 8, 16, 17, 15, 14, 12, 13};
      return opp[label];
    }
  }
}

int LocalParticle::oppositeDir(int dir) const {
  int opp[] {3, 4, 5, 0, 1, 2, 10, 11, 9, 8, 6, 7};
  return opp[dir];
}

int LocalParticle::mappedExpansion(int expandDir) const {
  Q_ASSERT(0 <= expandDir && expandDir < 12);
  return mappedLabel(expandDir);
}

int LocalParticle::mappedDir(int dir) const {
  Q_ASSERT(0 <= dir && dir < 12);
  return mappedLabel(dir);
}

int LocalParticle::mappedLabel(int label) const {
  int mappedLabel = label;
  std::vector<int> localLabels
      = labelMapping(latticeDir[Conversion::intToUInt(orientation % 6)]);
  for (int i = 0; i < localLabels.size(); ++i) {
    if (localLabels[Conversion::intToUInt(i)] == label) {
      mappedLabel = i;
    }
  }
  return mappedLabel;
}

std::vector<int> LocalParticle::surroundLabels(std::vector<int> labels) const {
  labels = adjacentLabels(labels);
  std::vector<int> shared = sharedLabels(labels);
  labels.insert(labels.end(), shared.begin(), shared.begin() + 2);
  return labels;
}

std::vector<int> LocalParticle::sharedLabels(std::vector<int> adjacentLabels)
const {
  std::vector<int> shared;
  std::vector<bool> checker(18);
  for (int i: adjacentLabels) {
    checker[Conversion::intToUInt(i)] = true;
  }
  if (oppositeDir(globalTailDir) < 6) {
    if (checker[2] & checker[6]) {
      shared.push_back(16);
      shared.push_back(9);
    }
    if (checker[3] & checker[7]) {
      shared.push_back(12);
      shared.push_back(14);
    }
    if (checker[1] & checker[5]) {
      shared.push_back(11);
      shared.push_back(13);
    }
  } else {
    if (oppositeDir(globalTailDir) == 6) {
      shared.push_back(6);
      shared.push_back(7);
      shared.push_back(4);
      shared.push_back(3);
    }
    if (oppositeDir(globalTailDir) == 7) {
      shared.push_back(9);
      shared.push_back(8);
      shared.push_back(4);
      shared.push_back(5);
    }
    if (oppositeDir(globalTailDir) == 8) {
      shared.push_back(10);
      shared.push_back(11);
      shared.push_back(3);
      shared.push_back(2);
    }
    if (oppositeDir(globalTailDir) == 9) {
      shared.push_back(1);
      shared.push_back(2);
      shared.push_back(11);
      shared.push_back(6);
    }
    if (oppositeDir(globalTailDir) == 10) {
      shared.push_back(3);
      shared.push_back(4);
      shared.push_back(10);
      shared.push_back(11);
    }
    if (oppositeDir(globalTailDir) == 11) {
      shared.push_back(0);
      shared.push_back(5);
      shared.push_back(11);
      shared.push_back(6);
    }
  }
  return shared;
}

std::vector<int> LocalParticle::adjacentLabels(std::vector<int> basisVector)
const {
  std::vector<int> adjLabels;
  std::vector<bool> checker(18);
  for (int i: basisVector) {
    checker[Conversion::intToUInt(i)] = true;
  }
  if (oppositeDir(globalTailDir) < 6) {
    if (checker[0] & checker[1]) {
      checker[8] = true;
    }
    if (checker[1] & checker[2]) {
      checker[13] = true;
    }
    if (checker[2] & checker[3]) {
      checker[14] = true;
    }
    if (checker[3] & checker[4]) {
      checker[10] = true;
    }
    if (checker[4] & checker[5]) {
      checker[15] = true;
    }
    if (checker[5] & checker[6]) {
      checker[11] = true;
    }
    if (checker[6] & checker[7]) {
      checker[12] = true;
    }
    if (checker[7] & checker[0]) {
      checker[17] = true;
    }
  } else {
    if (checker[0] & checker[1]) {
      checker[12] = true;
    }
    if (checker[2] & checker[3]) {
      checker[13] = true;
    }
    if (checker[4] & checker[5]) {
      checker[14] = true;
    }
    if (checker[7] & checker[8]) {
      checker[15] = true;
    }
    if (checker[9] & checker[10]) {
      checker[16] = true;
    }
    if (checker[6] & checker[11]) {
      checker[17] = true;
    }
  }
  for (int i = 0; i < checker.size(); ++i) {
    if (checker[Conversion::intToUInt(i)]) {
      adjLabels.push_back(i);
    }
  }
  return adjLabels;
}


