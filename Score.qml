import QtQuick 2.14

Rectangle {
    color: 'black'
    property int value: 0
    property int scoreHeight: Math.round(height * 0.4)
    property string team: 'Camille'

    onValueChanged: print("value", value)

    Letter {
        id: unit
        width: Math.round(height * 0.5)
        height: scoreHeight
        anchors.right: parent.right
        anchors.top: parent.top
        text: value % 10
        letterColor: team == 'Camille' ? "#fdd4d8" : "#f6fbdb"
        backgroundColor: team == 'Camille' ? "#bf3220" : "#d9ae14"
    }

    Letter {
        width: Math.round(height * 0.5)
        height: scoreHeight
        anchors.top: parent.top
        anchors.right: unit.left
        text: Math.floor(value * 0.1)
        letterColor: team == 'Camille' ? "#fdd4d8" : "#f6fbdb"
        backgroundColor: team == 'Camille' ? "#bf3220" : "#d9ae14"
    }


}
