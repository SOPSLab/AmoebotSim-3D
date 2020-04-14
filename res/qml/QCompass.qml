import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.12
import Qt3D.Input 2.0
import QtQuick 2.6

Entity {
  property Camera camera: Camera {
    id: camera
    projectionType: CameraLens.PerspectiveProjection
    fieldOfView: 20
    aspectRatio: 16/9
    nearPlane: 0.1
    farPlane: 500.0
    Component.onCompleted: {
      setCamera()
    }
  }

  components: [
    RenderSettings {
      activeFrameGraph: ForwardRenderer {
        camera: camera
        clearColor: Qt.rgba(0, 0, 0, 0)
      }
    },
    InputSettings {}
  ]

  // Mesh for compass directions.
  CylinderMesh {
    id: mesh
    radius: 0.025
    length: 0.25
    rings: 2
    slices: 10
  }

  // Blue arm pointing in +x direction.
  Entity {
    id: xArm
    PhongMaterial {
      id: xmaterial
      ambient: 'blue'
    }
    Transform {
      id: xtransform
      translation: Qt.vector3d(0.125, 0.0, 0.0)

      property real xRot: Math.acos(0 / mesh.length) * 180 / Math.PI
      property real yRot: Math.atan2(-1, 0) * 180 / Math.PI
      rotation: fromAxesAndAngles(Qt.vector3d(1, 0, 0), xRot,
                                  Qt.vector3d(0, 1, 0), yRot)
    }
    components: [mesh, xmaterial, xtransform]
  }
//  Text2DEntity {
//    id: xText
//    text: "X"
//    color: "blue"
//    height: 10
//    width: 10
//    Transform {
//      id: xTextTransform
//      translation: Qt.vector3d(0.3, -0.15, 0.0)
//      scale: .025
//    }
//    components: [xTextTransform]
//  }

  // Green arm pointing in +y direction.
  Entity {
    id: yArm
    PhongMaterial {
      id: ymaterial
      ambient: 'green'
    }
    Transform {
      id: ytransform
      translation: Qt.vector3d(0.0, 0.125, 0.0)

      property real xRot: Math.acos(-1) * 180 / Math.PI
      property real yRot: Math.atan2(0, 0) * 180 / Math.PI
      rotation: fromAxesAndAngles(Qt.vector3d(1, 0, 0), xRot,
                                  Qt.vector3d(0, 1, 0), yRot)
    }
    components: [mesh, ymaterial, ytransform]
  }
//  Text2DEntity {
//    id: yText
//    text: "Y"
//    color: "green"
//    height: 10
//    width: 10
//    Transform {
//      id: yTextTransform
//      translation: Qt.vector3d(-0.1, 0.3, 0.0)
//      scale: .025
//    }
//    components: [yTextTransform]
//  }

  // Red arm pointing in +z direction.
  Entity {
    id: zArm
    PhongMaterial {
      id: zmaterial
      ambient: 'red'
    }
    Transform {
      id: ztransform
      translation: Qt.vector3d(0.0, 0.0, 0.125)

      property real xRot: Math.acos(0 / mesh.length) * 180 / Math.PI
      property real yRot: Math.atan2(0, -1) * 180 / Math.PI
      rotation: fromAxesAndAngles(Qt.vector3d(1, 0, 0), xRot,
                                  Qt.vector3d(0, 1, 0), yRot)
    }
    components: [mesh, zmaterial, ztransform]
  }
//  Text2DEntity {
//    id: zText
//    text: "Z"
//    color: "red"
//    height: 10
//    width: 10
//    Transform {
//      id: zTextTransform
//      translation: Qt.vector3d(-0.05, 0, 0.3)
//      rotation: fromAxisAndAngle(Qt.vector3d(1,0,0), 90)
//      scale: .025
//    }
//    components: [zTextTransform]
//  }

  function setCamera() {
    camera.upVector = Qt.vector3d(0.0, 0.0, 1.0)
    camera.viewCenter = Qt.vector3d(0.0, 0.0, 0.0)
    camera.position = Qt.vector3d(0.0, -3.0, 0.0)
  }
}
