#include <cmath>

#include <QDebug>

#include "utility.h"

double Utility::distance3D(std::vector<double> x, std::vector<double> y) {
  Q_ASSERT(x.size() == 3 && y.size() == 3);
  return sqrt(pow(x[0] - y[0], 2) + pow(x[1] - y[1], 2) + pow(x[2] - y[2], 2));
}
