import Qt3D.Core 2.0
import Qt3D.Extras 2.0

Entity {
  property var properties
  property vector3d location: properties[0]
  property string color: properties[2]
  property vector3d mark: properties[4]

  Transform {
    id: sphereTransformer
    translation: location
  }

  SphereMesh {
    id: sphereMesh
    slices: 60
    rings: 60
    radius: 0.65
  }

  PhongMaterial {
    id: material
    ambient: color
  }

  QMarker {
    markDir: mark
    markerColor: color
  }

  components: [sphereTransformer, sphereMesh, material]
}
