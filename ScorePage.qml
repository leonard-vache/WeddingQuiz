import QtQuick 2.14

Rectangle {
    id: container
    color: "grey"

    Row {
        id: row
        property int availableWidth: container.width - spacing - 2*padding
        anchors.fill: parent
        spacing: 10
        //padding: 5

        Repeater {
            model: scorePage.teams
            Score {
                width: 0.5 * container.width - 5 // Math.round(0.5*(container.width - row.spacing - 2*row.padding))
                height: container.height
                // Model's attributes
                value: score
                team: name
                selected: model.selected

            }
        }
    }
}
