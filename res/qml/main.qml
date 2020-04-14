import QtQuick 2.11
import QtQuick.Scene3D 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import Qt3D.Render 2.12

Item {
  // Renders a 3D GUI scene for the particle system.
  Scene3D {
    anchors.fill: parent
    focus: true
    aspects: ["input", "logic"]
    cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

    // Creates an entity that holds the particle system.
    QSimulator {
      id: simulator
    }
  }

  // Renders an XYZ compass that rotates with the particle system.
  Scene3D {
    id: compassScene
    width: parent.width / 6
    height: parent.height / 6
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    anchors.margins: 10
    cameraAspectRatioMode: Scene3D.AutomaticAspectRatio
    aspects: ["input", "logic"]

    QCompass {
      id: compass
      Connections {
        target: simulator.camController
        onCameraPan: compass.camera.panAboutViewCenter(pan)
        onCameraTilt: compass.camera.tiltAboutViewCenter(tilt)
      }
    }
  }

  ColumnLayout {
    id: columnFormat
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.margins: 10
    width: parent.width / 6

    Rectangle {
      id: inspectionTextBox
      implicitWidth: parent.width
      implicitHeight: parent.height / 5
      Layout.alignment: Qt.AlignTop
      border.width: 1
      border.color: "#888"
      radius: 4
      color: "#eee"
      opacity: 0.8

      Text {
        id: inspectionText
        anchors.margins: 10
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        wrapMode: Text.Wrap
        color: "#000"
        text: "Particle Information";
        Connections {
          target: simulator.system
          onInspectionText: inspectionText.text = text
        }
      }
    }

    Button {
      id: cameraResetButton
      width: parent.width
      height: parent.height / 10      
      text: "Reset Camera"
      Layout.alignment: Qt.AlignRight | Qt.AlignBottom
      onClicked: {
        simulator.resetCameraPosition()
        compass.setCamera()
      }
    }
  }
}
