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

    property int displayedAnswer: 0
    property bool showResponse: false

    function reset() {
        showResponse = false
        displayedAnswer = 0
    }


//    MouseArea {
//        anchors.fill: container
//        onClicked: displayedAnswer = Math.min(displayedAnswer + 1, suggestions.length)
//    }


    Text {
        id: header
        padding: 10
        anchors.horizontalCenter: container.horizontalCenter
        width: container.width
        text: "Is this a Question ?"
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        font.family: fontName
        font.pixelSize: fontSize * 1.2
    }

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
                visible: displayedAnswer > index
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

    VideoContent {
        id: mediaContent
        visible: false
        anchors.centerIn: parent
        width: 800
        height: 600
        enabled: content != ""
        source: content
    }
}
