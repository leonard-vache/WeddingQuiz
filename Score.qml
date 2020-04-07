import QtQuick 2.14

Rectangle {
    color: 'black'
    property int score: 16
    property int scoreHeight: Math.round(height * 0.4)
    property string team: 'yellow'

    Letter {
        id: unit
        width: Math.round(height * 0.5)
        height: scoreHeight
        anchors.right: parent.right
        anchors.top: parent.top
        text: score % 10
        letterColor: team == 'red' ? "#fdd4d8" : "#f6fbdb"
        backgroundColor: team == 'red' ? "#bf3220" : "#d9ae14"
    }

    Letter {
        width: Math.round(height * 0.5)
        height: scoreHeight
        anchors.top: parent.top
        anchors.right: unit.left
        text: Math.floor(score / 10)
        letterColor: team == 'red' ? "#fdd4d8" : "#f6fbdb"
        backgroundColor: team == 'red' ? "#bf3220" : "#d9ae14"
    }
}
