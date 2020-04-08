import QtQuick 2.14
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
        width: window.width
        height: window.height

        MouseArea {
            anchors.fill: jingle
            onClicked: jingle.start()
        }
    }



//    MultipleChoiceQuestion {
//        width: window.width
//        height: window.height

//        questionText:  "What is the meaning of life ?"
//        answersText: ["TAGADA", "To be or not to be that is the question", "Cogito ergo sum", "La réponse D"]
//        responseIndex: 2
//    }

//    Score {
//        anchors.fill: parent
//    }

}
