import QtQuick 2.14

Item {
    id: container
    property string fontName: "HooliganJF"
    property int fontSize: 45

    property alias questionText: question.text
    property variant answersText: ["First", "Second", "Third", "Forth"]
    property int responseIndex: 0

    property int displayedAnswer: 0
    property bool showResponse: false

    MouseArea {
        anchors.fill: container
        onClicked: displayedAnswer = displayedAnswer + 1
        onDoubleClicked: showResponse = true
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
                opacity: showResponse && responseIndex !== index ? 0.5 : 1
                anchors.leftMargin : 10
                height: Math.round(answersArea.height / 4)

                Letter{
                    text: modelData
                    anchors.verticalCenter: parent.verticalCenter
                    height: parent.height
                    width: height
                }

                Text {
                    id: answer
                    anchors.verticalCenter: parent.verticalCenter
                    text: answersText[index]
                    font.family: fontName
                    font.pixelSize: fontSize
                }
            }
        }
    }
}
