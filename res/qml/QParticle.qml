import Qt3D.Core 2.0
import QtQuick 2.6
import Qt3D.Render 2.12

Entity {
  id: particle
  property bool expand: model.modelData[0] !== model.modelData[1]

  signal inspected(string text)

  Component.onCompleted: {
    var component = expand ? Qt.createComponent("QExpParticle.qml")
                           : Qt.createComponent("QConParticle.qml")
    if (component.status === Component.Ready){
      component.createObject(particle, {"properties": model.modelData})
    }
  }

  ObjectPicker {
    id: particlePicker
    onClicked: {
      if (pick.modifiers === Qt.AltModifier) {
        particle.inspected(model.modelData[6])
        // TODO: Remove once particles overwrite their own inspectionTexts.
        console.log(particle)
      }
    }
  }

  components: [particlePicker]
}
