import QtQuick 2.0

Item {
    id: container
    Row {
        spacing: 0
        Repeater {
            model: scorePage.teams
            Score {
                width:container.width * 0.5
                height:container.height
                value: score

            }
        }
    }
}
