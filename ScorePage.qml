import QtQuick 2.14

Rectangle {
    id: container
    color: "black"

    Row {
        id: row
        anchors.fill: parent
        spacing: 10
        padding: 5

        Repeater {
            model: scorePage.teams
            Score {
                width: 0.5*container.width - 20
                height: container.height
                // Model's attributes
                value: score
                team: name

            }
        }
    }
}
