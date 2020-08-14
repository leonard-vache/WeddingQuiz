import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Window 2.2
import QtMultimedia 5.14

import WeddingQuiz 1.0


Window {
    id: window
    visible: true
    width: 1920
    height: 1080
    title: qsTr("Wedding Quiz")
    // Full screen
    flags: Qt.Window | Qt.FramelessWindowHint
    //flags: Qt.Window

    Item {
        anchors.fill: parent
        focus:true
        Keys.onPressed: remote.keyChanged(event.key)

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.AllButtons
            onClicked:
            {
                 remote.keyChanged(mouse.button)
            }
        }
    }


    PageController {
        anchors.fill: parent
    }

}
