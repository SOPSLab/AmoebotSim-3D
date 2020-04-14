#include <cmath>

#include <QDebug>

#include "helper/conversion.h"

uint Conversion::intToUInt(int i) {
  if (i < 0) {
    qDebug() << "Trying to convert negative signed int to unsigned int";
    return 0;
  } else {
    return static_cast<uint>(i);
  }
}

std::vector<double> Conversion::cartesianPos(std::vector<int> latticePos) {
  int x_l = latticePos[0];
  int y_l = latticePos[1];
  int z_l = latticePos[2];

  double x_c = x_l + y_l/2.0 + z_l/2.0;
  double y_c = sqrt(3.0)/2.0 * y_l - sqrt(3.0)/6.0 * z_l;
  double z_c = sqrt(6.0)/3.0 * z_l;

  return {x_c, y_c, z_c};
}

QVector3D Conversion::vecToQVec3D(std::vector<double> vec) {
  Q_ASSERT(vec.size() == 3);
  return {static_cast<float>(vec[0]), static_cast<float>(vec[1]),
          static_cast<float>(vec[2])};
}
