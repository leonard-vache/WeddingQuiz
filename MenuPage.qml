import QtQuick 2.14
import WeddingQuiz.Common 1.0


Item {
    id: root

    property int currentButton: 0
    property int letterWidth: 30
    property int letterHeight: 2 * letterWidth

    height: childrenRect.height


    Rectangle {
        id: score
        enabled: currentButton === Common.E_BUTTON_SCORE
        opacity: enabled ? 1.0 : 0.3
        width: childrenRect.width
        height: childrenRect.height
        anchors { left: root.left; leftMargin: letterWidth }


        Repeater
        {
            model: ["S","C","O","R","E"]
            Letter {
                text: modelData
                letterColor: index % 2 == 0 ? "#fdd4d8" : "#f6fbdb"
                backgroundColor: index % 2 == 0 ? "#bf3220" : "#d9ae14"
                width: letterWidth
                height: letterHeight
                x: index * letterWidth
            }
        }
    }

    Rectangle {
        id: content
        enabled: currentButton === Common.E_BUTTON_CONTENT
        opacity: enabled ? 1.0 : 0.3
        width: childrenRect.width
        height: childrenRect.height
        anchors { right: root.right; rightMargin: letterWidth }

        Repeater
        {
            model: ["C","O","N","T","E","N","T"]
            Letter {
                text: modelData
                letterColor: "#8fdbfb"
                backgroundColor: "#4941ae"
                width: letterWidth
                height: letterHeight
                x: index * letterWidth
            }
        }
    }


}
