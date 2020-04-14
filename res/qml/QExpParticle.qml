import Qt3D.Core 2.0
import Qt3D.Extras 2.0
import QtQuick 2.6

Entity {
  property var properties
  property vector3d headLocation: properties[0]
  property vector3d tailLocation: properties[1]
  property string headColor: properties[2]
  property string tailColor: properties[3]
  property vector3d headMark: properties[4]
  property vector3d tailMark: properties[5]

  // Render the head node.
  QConParticle {
    location: headLocation
    color: headColor
    mark: headMark
  }

  // Render the tail node.
  QConParticle {
    location: tailLocation
    color: tailColor
    mark: tailMark
  }

  // Render connector between head and tail node.
  QEdge {
    start: headLocation
    end: tailLocation
    radius_: 0.3
    expanded: true
  }
}
