import QtQuick 2.14
import QtQuick.Controls 2.12

Item {
    id: container
    property string fontName: "HooliganJF"
    property int fontSize: 85
    property alias heading: header.text
    property variant suggestions: ["First", "Second", "Third", "Forth"]
    property int answer: 0
    property int reward: 0
    property string content: "" 
    property int headingAvailableWidth: root.width

    property real suggestionIndex: -1
    property bool showResponse: false

    function reset() {
        showResponse = false
        suggestionIndex = -1
    }


//    MouseArea {
//        anchors.fill: container
//        onClicked: displayedAnswer = Math.min(displayedAnswer + 1, suggestions.length)
//    }


    Text {
        id: header
        padding: 10
        x: 180
//        anchors.horizontalCenter: container.horizontalCenter
        width: root.width - 420
        text: "Is this a Question ?"
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        font.family: fontName
        font.pixelSize: fontSize * 1

//        onWidthChanged: print(headingAvailableWidth)

    }

//    Rectangle {
//        anchors.fill: header
//        border.color:"red"
//        color: "transparent"
//        border.width:1
//    }


    Item {
        id: answersArea
        anchors.top: header.bottom
        width: container.width
        height: container.height - header.height

        property int spacing: Math.round(height * 0.01)
        property int linesHeight: Math.round((height - 3 * spacing) * 0.25)

        Repeater {
            model: ["A", "B", "C", "D"]

            Row {
                visible: suggestionIndex >= index
                opacity: showResponse && answer !== index ? 0.5 : 1
                anchors.leftMargin : 10
                y: index * (answersArea.linesHeight+answersArea.spacing)

                Letter {
                    id: headingLetter
                    text: modelData
                    anchors.verticalCenter: parent.verticalCenter
                    height: answersArea.linesHeight
                    width: height
                }

                Text {
                    id: suggestion
                    anchors.verticalCenter: parent.verticalCenter
                    width: container.width - headingLetter.width
                    text: suggestions[index]
                    font.family: fontName
                    font.pixelSize: fontSize
                    wrapMode: Text.WordWrap

//                    TextMetrics{id: metrics; font: suggestion.font; text: suggestion.text}
                }

            }
        }
    }

}
