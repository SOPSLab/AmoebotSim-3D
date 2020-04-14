// Defines a class representing nodes in lattice space.

#ifndef AMOEBOTSIM_CORE_NODE_H_
#define AMOEBOTSIM_CORE_NODE_H_

#include <array>

#include <QtGlobal>

class Node {
 public:
  // Node constructors. The default constructor makes the origin node (0, 0, 0),
  // the second constructs a node (x, y, z), and the third copies the input node.
  Node();
  Node(int x, int y, int z);
  Node(const Node& other);

  // Equality operators; == returns true if the two nodes are equal and != does
  // the opposite.
  bool operator==(const Node& other) const;
  bool operator!=(const Node& other) const;

  // Returns the node in global direction dir from this node.
  Node nodeInDir(uint dir) const;

  int x, y, z;
};

inline Node::Node()
  : x(0), y(0), z(0) {}

inline Node::Node(int x, int y, int z)
  : x(x), y(y), z(z) {}

inline Node::Node(const Node& other)
  : x(other.x), y(other.y), z(other.z) {}

inline bool Node::operator==(const Node& other) const {
  return (x == other.x) && (y == other.y) && (z == other.z);
}

inline bool Node::operator!=(const Node& other) const {
  return !operator==(other);
}

inline Node Node::nodeInDir(uint dir) const {
  static constexpr std::array<int, 12> xOffset = {{1,  1,  0, -1, -1, 0, 0, -1, -1,  1,  0,  1}};
  static constexpr std::array<int, 12> yOffset = {{0, -1, -1,  0,  1, 1, 0,  0,  1, -1,  0,  0}};
  static constexpr std::array<int, 12> zOffset = {{0,  0,  0,  0,  0, 0, 1,  1,  1, -1, -1, -1}};

  return Node(x + xOffset[dir], y + yOffset[dir], z + zOffset[dir]);
}


#endif  // AMOEBOTSIM_CORE_NODE_H_
