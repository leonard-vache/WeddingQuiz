import QtQuick 2.14

Rectangle {
    id: root

    property int value: 0
    property int scoreHeight: Math.round(height * 0.4)
    property string team: 'Camille'
    property bool selected: false

    function getTextColor() {

        if(team == 'Camille')
            return selected ? "#bf3220" : "#fdd4d8"
        else
            return selected ? "#d9ae14" : "#f6fbdb"
    }

    color: 'black'

    Text {
        id: teamLabel
        opacity: selected ? 1.0 : 0.5
        text: team
        font.family: "HooliganJF"
        font.pixelSize: height * 0.5
        anchors { left: root.left; right: ten.left }
        height: scoreHeight * 0.5
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter
        color: getTextColor()
    }


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
        id: ten
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
        spacing: 0.15 * parent.width / 3
        padding: 0.05 * parent.width

        Item {
            id:cake
            width: row.availableWidth * 0.475
            height: row.availableHeight * 0.95

            Repeater {
                model: [1,2,3,4,5,6,7,8,9]

                Image {
                    anchors.bottom: parent.bottom
                    opacity:  modelData < value ? 1.0 : 0.3
                    source: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/score_clean_" + modelData.toFixed() + ".png"
                    fillMode: Image.PreserveAspectFit
                    width: cake.width
                }

            } // end of Repeater

        } // end of Item (id: cake)


        Item {
            id: champagne
            width: row.availableWidth * 0.29
            height: row.availableHeight * 0.95

            Repeater {
                model: [10, 11, 12, 13, 14, 15]

                Image {
                    anchors.bottom: parent.bottom

                    opacity:  modelData <= value ? 1.0 : 0.3
                    source: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/score_clean_" + modelData.toFixed() + ".png"
                    fillMode: Image.PreserveAspectFit
                    width: champagne.width
                }

            } // end of Repeater

        } // end of Item (id: champagne)


        Item {
            id: glasses
            width: row.availableWidth * 0.19
            height: row.availableHeight * 0.95

            Repeater {
                model: [16, 17]

                Image {
                    anchors.bottom: parent.bottom
                    opacity:  modelData < value ? 1.0 : 0.3
                    source: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/score_clean_" + modelData.toFixed() + ".png"
                    fillMode: Image.PreserveAspectFit
                    width: glasses.width
                }

            } // end of Repeater

        } // end of Item (id: glasses)

    } // end of Row (id: row)

}
