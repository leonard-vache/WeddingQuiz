import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Window 2.2
import QtMultimedia 5.14

import WeddingQuiz 1.0


Window {
    id: window
    visible: true
    width: 1920
    height: 1080
    title: qsTr("Wedding Quiz")
    // Full screen
    //flags: Qt.Window | Qt.FramelessWindowHint

    Item {
        anchors.fill: parent
        focus:true
        Keys.onPressed: remote.keyChanged(event.key)
    }




    PageController {
        anchors.fill: parent
    }




    property MultipleChoicesQuestionObject qModel: questions.mcq

    MultipleChoicesQuestionItem {
        id: mcq
        visible: bMcq.checked && ! jingle.running
        width: window.width
        height: window.height

        heading:  qModel.heading
        suggestions: qModel.suggestions
        answer: qModel.answer-1
        content: qModel.content

        onNext: { mcq.reset(); questions.next() }
    }





    Column {
        visible: true
        width: 100
        spacing: 4
//        Button {
//            id: bJingle
//            width: parent.width
//            height: width * 0.5
//            text: "Jingle"
//            onClicked: {jingle.reset(); jingle.start()}
//        }

        Button {
            id: bMcq
            width: parent.width
            height: width * 0.5
            text: "MCQ"
            checkable: true
            onCheckedChanged: {
                if(checked == false) mcq.reset()
//                else jingle.visible = false
            }
        }


    }

    Item {
        anchors.fill: parent
        focus:true
        Keys.onPressed: remote.keyChanged(event.key)
    }

}
