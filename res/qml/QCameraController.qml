import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0

Entity {
  id: controller
  property Camera camera
  property real deltaLook: 0.005
  property real deltaLinear: 0.001
  property real deltaZoom: 0.001
  property real linearSpeed: 100
  property real lookSpeed: 100
  property real zoomLimit: 15

  // Property and signal for switching between 2D and 3D camera modes.
  property bool in3DMode
  signal switchTo2DMode()

  // Signals for when the camera pans or tilts.
  signal cameraPan(var pan)
  signal cameraTilt(var tilt)

  KeyboardDevice {
    id: keyboardinput
  }

  // Defines the movement controlled by the keyboard. Up/Down/Left/Right Arrows
  // translate the camera in the respective direction. Up (or) Down + Shift
  // tilts about the view center. Left (or) Right + Shift pans the camera
  // about the view center.
  KeyboardHandler {
    sourceDevice: keyboardinput
    focus: true
    onPressed: {
      if ((event.modifiers & Qt.ShiftModifier) && in3DMode) {
        var tilt = deltaLook * lookSpeed * 10
        var pan = deltaLook * lookSpeed * 10
        if (event.key === Qt.Key_Up) {
          camera.tiltAboutViewCenter(tilt)
          cameraTilt(tilt)
        } else if (event.key === Qt.Key_Down) {
          camera.tiltAboutViewCenter(-tilt)
          cameraTilt(-tilt)
        } else if (event.key === Qt.Key_Right) {
          camera.panAboutViewCenter(-pan)
          cameraPan(-pan)
        } else if (event.key === Qt.Key_Left) {
          camera.panAboutViewCenter(pan)
          cameraPan(pan)
        }
      } else {
        if (event.key === Qt.Key_Up) {
          camera.translate(Qt.vector3d(0, 5 * deltaLinear * linearSpeed, 0))
        } else if (event.key === Qt.Key_Down) {
          camera.translate(Qt.vector3d(0, -5 * deltaLinear * linearSpeed, 0))
        } else if (event.key === Qt.Key_Right) {
          camera.translate(Qt.vector3d(5 * deltaLinear * linearSpeed, 0, 0))
        } else if (event.key === Qt.Key_Left) {
          camera.translate(Qt.vector3d(-5 * deltaLinear * linearSpeed, 0, 0))
        }
      }

      if (event.key === Qt.Key_2) {
        if (in3DMode) {
          switchTo2DMode()
        }
        controller.in3DMode = false
      } else if (event.key === Qt.Key_3) {
        controller.in3DMode = true
      }
    }
  }

  MouseDevice {
    id: mouseDevice
    sensitivity: 0.001
  }

  // Defines the movement controlled by the mouse. Left click + drag translates
  // the camera. Right click + drag pans & tilts the camera about the view
  // center. Left & Right click + drag [or mouse wheel] zooms in/out
  MouseHandler {
    id: mouseHandle
    sourceDevice: mouseDevice
    property point lastPosition
    property real pan
    property real tilt

    onPressed: { lastPosition = Qt.point(mouse.x, mouse.y) }
    onWheel: { zoom(wheel.angleDelta.y * deltaZoom * linearSpeed) }
    onPositionChanged: {
      if (mouse.buttons === 1 || (mouse.buttons === 2 && !in3DMode)) {
        var rx = -(mouse.x - lastPosition.x) * deltaLinear * linearSpeed
        var ry = (mouse.y - lastPosition.y) * deltaLinear * linearSpeed
        camera.translate(Qt.vector3d(rx, ry, 0))
      } else if (mouse.buttons === 2 && in3DMode) {
        pan = -(mouse.x - lastPosition.x) * deltaLook * lookSpeed
        tilt = (mouse.y - lastPosition.y) * deltaLook * lookSpeed
      } else if (mouse.buttons === 3) {
        zoom((mouse.y - lastPosition.y) * deltaZoom * linearSpeed)
      }

      lastPosition = Qt.point(mouse.x, mouse.y)
    }
    onPanChanged: {
      camera.panAboutViewCenter(pan)
      cameraPan(pan)
    }
    onTiltChanged: {
      camera.tiltAboutViewCenter(tilt)
      cameraTilt(tilt)
    }

    function zoom(zoomVal) {
      var zoomDistance = camera.viewCenter.minus(camera.position).length()
      if (zoomVal <= 0 || zoomDistance >= zoomLimit) {
        camera.translate(Qt.vector3d(0, 0, zoomVal),
                         Camera.DontTranslateViewCenter)
      }
    }
  }
}
