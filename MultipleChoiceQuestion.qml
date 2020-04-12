import QtQuick 2.14
import QtQuick.Controls 2.12

Item {
    id: container
    property string fontName: "HooliganJF"
    property int fontSize: 45

    property alias heading: question.text
    property variant suggestions: ["First", "Second", "Third", "Forth"]
    property int answer: 0
    property int reward: 0

    property int displayedAnswer: 0
    property bool showResponse: false

    function reset() {
        displayedAnswer = 0
    }

    signal scoring( int value )

    MouseArea {
        anchors.fill: container
        onClicked: displayedAnswer = Math.min(displayedAnswer + 1, suggestions.length)
    }

    Button {
        id: bAnswer
        visible: displayedAnswer == suggestions.length
        anchors.top: parent.top
        anchors.right: parent.right
        width: 100
        height: 50
        text:"ANSWER"
        onClicked: showResponse = true
    }

    Button {
        visible: displayedAnswer == suggestions.length
        anchors.top: bAnswer.bottom
        anchors.right: parent.right
        width: 100
        height: 50
        text:"SCORING"
        onClicked: scoring(reward)
    }



    Text {
        id: question
        padding: 10
        anchors.horizontalCenter: container.horizontalCenter
        width: container.width
        text: "Is this a Question ?"
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        font.family: fontName
        font.pixelSize: fontSize * 1.2
    }

    Column {
        id: answersArea
        anchors.top: question.bottom
        width: container.width
        height: container.height - question.height

        spacing: Math.round(height * 0.01)

        Component.onCompleted: print(container.height, question.height, spacing)

        Repeater {
            model: ["A", "B", "C", "D"]

            Row {
                visible: displayedAnswer > index
                opacity: showResponse && answer !== index ? 0.5 : 1
                anchors.leftMargin : 10
                height: Math.round(answersArea.height / 4)

                Letter{
                    text: modelData
                    anchors.verticalCenter: parent.verticalCenter
                    height: parent.height
                    width: height
                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: suggestions[index]
                    font.family: fontName
                    font.pixelSize: fontSize
                }
            }
        }
    }
}
