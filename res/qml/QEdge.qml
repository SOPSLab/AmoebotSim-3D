import Qt3D.Core 2.0
import Qt3D.Extras 2.0
import QtQuick 2.6

Entity {
  property var edges
  property vector3d start: edges[0]
  property vector3d end: edges[1]
  property real radius_: 0.1
  property bool expanded

  // Render the cylinder connecting the adjacent nodes.
  property real dX: (start.x - end.x)
  property real dY: (start.y - end.y)
  property real dZ: (start.z - end.z)
  property real magnitude: Math.sqrt(dX*dX + dY*dY + dZ*dZ)

  CylinderMesh {
    id: mesh
    radius: radius_
    length: magnitude
    rings: 2
    slices: 20
  }

  Transform {
    id: transform
    translation: Qt.vector3d((start.x + end.x) / 2.0,
                             (start.y + end.y) / 2.0,
                             (start.z + end.z) / 2.0)

    property real xRot: Math.acos(dY / magnitude) * 180 / Math.PI
    property real yRot: Math.atan2(dX, dZ) * 180 / Math.PI
    rotation: fromAxesAndAngles(Qt.vector3d(1, 0, 0), xRot,
                                Qt.vector3d(0, 1, 0), yRot)
  }

  PhongMaterial {
    id: material
    ambient: expanded ? "black" : "lightgrey"
  }

  components: [mesh, material, transform]
}


