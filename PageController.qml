import QtQuick 2.14

Item {
    id: control

    signal next()

    MouseArea {
        anchors.fill: parent
        onClicked: {

            control.next()
        }

    }


}
