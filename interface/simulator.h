// Defines a simulator used as an interface between C++ and QML objects.

#ifndef AMOEBOTSIM_INTERFACE_SIMULATOR_H_
#define AMOEBOTSIM_INTERFACE_SIMULATOR_H_

// TODO: the following are only needed for testing systemChanged(). Remove after
// this is integrated at a deeper level.
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <QDebug>

#include <memory>

#include <QList>
#include <QObject>

#include "core/system.h"

class Simulator : public QObject {
  Q_OBJECT
  Q_PROPERTY(QList<QVariant> particles READ getParticles NOTIFY particleSignal)
  Q_PROPERTY(QList<QVariant> edges READ getEdges NOTIFY edgeSignal)

 signals:
  void systemChanged() const;
  void particleSignal();
  void edgeSignal();

 public:
  // Default constructor (currently creates a System shared pointer).
  Simulator();

  // TODO: Remove after systemChanged() is integrated at a deeper level.
  void doPeriodically(std::function<void(void)> f, uint period);
  void callSystemChanged();

  // Returns the list of all particles' head/tail node locations in Cartesian
  // coordinates, colors, and markers. Primarily used by QML rendering.
  QList<QVariant> getParticles() const;

  // Returns the list of edges between adjacent, occupied nodes to be displayed
  // in the scene. Each QVariant in the QList contains a QList of the start
  // and end locations of the edge.
  QList<QVariant> getEdges() const;

 private:
  // Simulator properties.
  std::shared_ptr<System> _system;  // Shared pointer to particle system.
  float _spacing = 2;  // Separation factor between rendered nodes.

  // Returns the Cartesian position of a node marker belonging to the given node
  // and pointing in the specified direction.
  std::vector<double> markerPosInDir(Node marked, int dir) const;
};

#endif  // AMOEBOTSIM_INTERFACE_SIMULATOR_H_
