import QtQuick 2.14

Rectangle {
    id: root

    property int value: 0
    property int scoreHeight: Math.round(height * 0.4)
    property string team: 'Camille'

    color: 'black'

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

    Row {
        id: row

        property int availableWidth: root.width - 2*padding - 2*spacing
        property int availableHeight: root.height - 2*padding

        width: parent.width
        height: parent.height
        spacing: 20
        padding: 10

        Item {
            id:cake
            width: row.availableWidth * 0.42
            height: row.availableHeight * 0.95

            Repeater {
                model: [1,2,3,4,5,6,7,8,9]

                Image {
                    anchors.bottom: parent.bottom
                    opacity:  modelData < value ? 1.0 : 0.3
                    source: "resources/score_clean_" + modelData.toFixed() + ".png"
                    fillMode: Image.PreserveAspectFit
                    width: cake.width
                }

            } // end of Repeater

        } // end of Item (id: cake)


        Item {
            id: champagne
            width: row.availableWidth * 0.28
            height: row.availableHeight * 0.95

            Repeater {
                model: [10, 11, 12, 13, 14, 15]

                Image {
                    anchors.bottom: parent.bottom

                    opacity:  modelData <= value ? 1.0 : 0.3
                    source: "resources/score_clean_" + modelData.toFixed() + ".png"
                    fillMode: Image.PreserveAspectFit
                    width: champagne.width
                }

            } // end of Repeater

        } // end of Item (id: champagne)


        Item {
            id: glasses
            width: row.availableWidth * 0.2
            height: row.availableHeight * 0.95

            Repeater {
                model: [16, 17]

                Image {
                    anchors.bottom: parent.bottom
                    opacity:  modelData < value ? 1.0 : 0.3
                    source: "resources/score_clean_" + modelData.toFixed() + ".png"
                    fillMode: Image.PreserveAspectFit
                    width: glasses.width
                }

            } // end of Repeater

        } // end of Item (id: glasses)

    } // end of Row (id: row)

}
