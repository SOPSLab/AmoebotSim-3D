// Helper library of algebraic functions.

#ifndef AMOEBOTSIM_HELPER_UTILITY_H_
#define AMOEBOTSIM_HELPER_UTILITY_H_

#include <vector>

class Utility {
 public:
  // Computes the distance between two points in (Cartesian) 3D space.
  // Fails if the input vectors are not of size 3.
  static double distance3D(std::vector<double> x, std::vector<double> y);
};

#endif  // AMOEBOTSIM_HELPER_UTILITY_H_
