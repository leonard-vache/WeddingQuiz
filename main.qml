import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 1000
    height: 800
    title: qsTr("Wedding Quiz")

//    MouseArea {
//        anchors.fill: parent
//        onClicked: jingle.start()

//    }

//    Jingle {
//        id: jingle
//        width: window.width
//        height: window.height
//    }

    MultipleChoiceQuestion {
        width: window.width
        height: window.height

        questionText:  "What is the meaning of life ?"
        answersText: ["TAGADA", "To be or not to be that is the question", "Cogito ergo sum", "La réponse D"]
        responseIndex: 2
    }

}
