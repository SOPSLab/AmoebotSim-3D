import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import QtQuick 2.6

Entity {
  property bool in3DMode: false

  Camera {
    id: camera
    projectionType: CameraLens.PerspectiveProjection
    fieldOfView: 45
    aspectRatio: 16/9
    nearPlane: 0.1
    farPlane: 1000.0
    Component.onCompleted: {
      resetCameraPosition()
    }
  }

  property QCameraController camController: QCameraController {
    id: camController
    camera: camera
    in3DMode: in3DMode
    onSwitchTo2DMode: set2DCamera()
  }

  components: [
    RenderSettings {
      activeFrameGraph: ForwardRenderer {
        camera: camera
        clearColor: Qt.rgba(0, 0.5, 1, 1)
      }
    },
    InputSettings {}
  ]

  Entity {
    id: lightSource
    components: [
      PointLight {
        color: "white"
        intensity: 0.4
      },
      Transform {
        translation: camera.position.plus(Qt.vector3d(0, -5, 0))
      }
    ]
  }

  property QSystem system : QSystem {
    id: systemLink
    modelParticles: sim.particles
    modelEdges: sim.edges
  }

  Connections {
    target: sim
    onSystemChanged: refreshSystem()
  }

  function resetCameraPosition() {
    if (in3DMode) {
      camera.viewCenter = centerOfMass()
      camera.position = Qt.vector3d(camera.viewCenter.x, minYPosition() - 40,
                                    camera.viewCenter.z)
      camera.upVector = Qt.vector3d(0.0, 0.0, 1.0)
    } else {
      set2DCamera()
    }
  }

  function set2DCamera() {
    camera.viewCenter = centerOfMass()
    camera.position = Qt.vector3d(camera.viewCenter.x, camera.viewCenter.y,
                                  maxZPosition() + 40)
    camera.upVector = Qt.vector3d(0.0, 1.0, 0.0)
  }

  function centerOfMass() {
    var sumX = 0;
    var sumY = 0;
    var sumZ = 0;

    // Calculates the sum of head and tail locations of all particles
    for (var i = 0; i < sim.particles.length; i++) {
      sumX += sim.particles[i][0].x + sim.particles[i][1].x
      sumY += sim.particles[i][0].y + sim.particles[i][1].y
      sumZ += sim.particles[i][0].z + sim.particles[i][1].z
    }

    // Returns the center of mass of all particles by taking average of sums.
    var numNodes = 2.0 * sim.particles.length
    return Qt.vector3d(sumX / numNodes, sumY / numNodes, sumZ / numNodes)
  }

  function minYPosition() {
    var minYPos = Number.MAX_SAFE_INTEGER

    // Finds the minimum y-position in the particle system.
    for (var i = 0; i < sim.particles.length; i++) {
      if (Math.min(sim.particles[i][0].y, sim.particles[i][1].y) < minYPos) {
        minYPos = Math.min(sim.particles[i][0].y, sim.particles[i][1].y)
      }
    }

    return minYPos
  }

  function maxZPosition() {
    var maxZPos = Number.MIN_SAFE_INTEGER

    // Finds the maximum z-position in the particle system.
    for (var i = 0; i < sim.particles.length; i++) {
      if (Math.max(sim.particles[i][0].z, sim.particles[i][1].z) > maxZPos) {
        maxZPos = Math.max(sim.particles[i][0].z, sim.particles[i][1].z)
      }
    }

    return maxZPos
  }

  function refreshSystem() {
    systemLink.modelParticles = sim.particles
    systemLink.modelEdges = sim.edges
  }
}

