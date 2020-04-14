import Qt3D.Core 2.0
import QtQuick 2.12

Entity {
  property var modelParticles
  property var modelEdges

  signal inspectionText(string text)

  // NodeInstantiator passes each piece of the model to each particle delegate.
  NodeInstantiator {
    id: nodes
    model: modelParticles
    delegate: QParticle {
      Component.onCompleted: { inspected.connect(inspectionText) }
    }
  }

  // Assigns and manages each lattice edge between adjacent, occupied particles
  // as a QEdge delegate.
  NodeInstantiator {
    id: edges
    model: modelEdges
    delegate: QEdge {edges: model.modelData}
  }
}
