import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 1920
    height: 1080
    title: qsTr("Wedding Quiz")
    // Full screen
    //flags: Qt.Window | Qt.FramelessWindowHint


    Jingle {
        id: jingle
        visible: false
        width: window.width
        height: window.height
        onRunningChanged: if(running) visible = true
    }


    MultipleChoiceQuestion {
        id: mcq
        visible: bMcq.checked && ! jingle.running
        width: window.width
        height: window.height

        heading:  qm.heading
        suggestions: qm.suggestions
        answer: qm.answer-1
        reward: qm.reward
    }

    Score {
        id: score
        visible: bScore.checked && ! jingle.running
        anchors.fill: parent
    }


    Column {
        visible: ! jingle.running
        width: 100
        spacing: 4
        Button {
            id: bJingle
            width: parent.width
            height: width * 0.5
            text: "Jingle"
            onClicked: {jingle.reset(); jingle.start()}
        }

        Button {
            id: bMcq
            width: parent.width
            height: width * 0.5
            text: "MCQ"
            checkable: true
            onCheckedChanged: {
                if(checked == false) mcq.reset()
                else jingle.visible = false
            }
        }

        Button {
            id: bScore
            width: parent.width
            height: width * 0.5
            text: "Score"
            checkable: true
            onCheckedChanged: if(checked == true) jingle.visible = false
        }
    }
}
