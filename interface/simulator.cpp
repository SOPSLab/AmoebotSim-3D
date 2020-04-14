#include <QColor>
#include <QtMath>
#include <QVector3D>

#include "helper/conversion.h"
#include "helper/utility.h"
#include "interface/simulator.h"

Simulator::Simulator() {
  _system = std::make_shared<System>();

  // TODO: Remove after systemChanged() is integrated.
  std::function<void(void)> f(std::bind(&Simulator::callSystemChanged, this));
  doPeriodically(f, 3000);
}

// TODO: Remove after systemChanged() is integrated.
void Simulator::doPeriodically(std::function<void(void)> f, uint period) {
  std::thread([f, period]() {
    while (true) {
      f();
      std::this_thread::sleep_for(std::chrono::milliseconds(period));
    }
  }).detach();
}

// TODO: Remove after systemChanged() is integrated.
void Simulator::callSystemChanged() {
  systemChanged();
  qDebug() << "system changed!";
}

QList<QVariant> Simulator::getParticles() const {
  QList<QVariant> particleModel;
  std::vector<Particle> particles = _system->getParticles();
  for (Particle const &p : particles) {
    Node head = p.head;
    Node tail = p.tail();

    std::vector<double> headPos
        = Conversion::cartesianPos({head.x, head.y, head.z});
    std::vector<double> tailPos
        = Conversion::cartesianPos({tail.x, tail.y, tail.z});

    QColor headColor =
        QColor::fromRgb(Conversion::intToUInt(p.headMarkColor()));
    QColor tailColor =
        QColor::fromRgb(Conversion::intToUInt(p.tailMarkColor()));

    std::vector<double> headMarkerPos =
        markerPosInDir(head, p.globalHeadMarkDir());
    std::vector<double> tailMarkerPos =
        markerPosInDir(tail, p.globalTailMarkDir());

    particleModel.push_back(
          QVariant({_spacing * Conversion::vecToQVec3D(headPos),
                    _spacing * Conversion::vecToQVec3D(tailPos),
                    headColor, tailColor,
                    _spacing * Conversion::vecToQVec3D(headMarkerPos),
                    _spacing * Conversion::vecToQVec3D(tailMarkerPos),
                    p.inspectionText()}));
  }

  return particleModel;
}

QList<QVariant> Simulator::getEdges() const {
  QList<QVariant> edgeModel;
  std::vector<Particle> particles = _system->getParticles();
  for (Particle const &p : particles) {
    std::vector<double> head =
        Conversion::cartesianPos({p.head.x, p.head.y, p.head.z});
    std::vector<double> tail =
        Conversion::cartesianPos({p.tail().x, p.tail().y, p.tail().z});

    /* Some of following functions have not been implemented yet but will be
     * once AmoebotParticle is finished. I provide the more efficient code in
     * comments in order to ensure the program compiles.
     *
     * for (int dir = 0; dir < 12; ++dir) {
     *   if (p.hasNbrAtLabel(dir)) {
     *     Particle q = p.nbrAtLabel(dir);
     *     ...
     *   }
     * }
    */
    for (Particle const &q : particles) {
      std::vector<double> qHead =
          Conversion::cartesianPos({q.head.x, q.head.y, q.head.z});
      std::vector<double> qTail =
          Conversion::cartesianPos({q.tail().x, q.tail().y, q.tail().z});

      if (Utility::distance3D(head, qHead) <= sqrt(159)/12) {
        edgeModel.push_back(
              QVariant({_spacing * Conversion::vecToQVec3D(head),
                        _spacing * Conversion::vecToQVec3D(qHead)}));
      }
      if (Utility::distance3D(head, qTail) <= sqrt(159)/12) {
        edgeModel.push_back(
              QVariant({_spacing * Conversion::vecToQVec3D(head),
                        _spacing * Conversion::vecToQVec3D(qTail)}));
      }
      if (Utility::distance3D(tail, qHead) <= sqrt(159)/12) {
        edgeModel.push_back(
              QVariant({_spacing * Conversion::vecToQVec3D(tail),
                        _spacing * Conversion::vecToQVec3D(qHead)}));
      }
      if (Utility::distance3D(tail, qTail) <= sqrt(159)/12) {
        edgeModel.push_back(
              QVariant({_spacing * Conversion::vecToQVec3D(tail),
                        _spacing * Conversion::vecToQVec3D(qTail)}));
      }
    }
  }

  return edgeModel;
}

std::vector<double> Simulator::markerPosInDir(Node marked, int dir) const {
  if (dir != -1) {
    Node target = marked.nodeInDir(Conversion::intToUInt(dir));
    std::vector<double> targetPos
        = Conversion::cartesianPos({target.x, target.y, target.z});
    std::vector<double> nodePos
        = Conversion::cartesianPos({marked.x, marked.y, marked.z});

    double offset = 0.25;
    return {offset * (targetPos[0] - nodePos[0]),
            offset * (targetPos[1] - nodePos[1]),
            offset * (targetPos[2] - nodePos[2])};
  } else {
    return {0,0,0};
  }
}


