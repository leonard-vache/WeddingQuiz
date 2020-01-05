import QtQuick 2.9

Rectangle {
    id: container

    color: "black"

    function start() {
        wedd.children[0].start()
        wedd.visible = true
    }

    Row {
        id: wedd
        visible: false
        anchors.horizontalCenter: container.horizontalCenter
        Repeater {
            id: weddRepeater
            model:["W","E","D","D","I","N","G"]

            delegate: Letter {

                function start() {
                    anim.start()
                }

                text: modelData
                letterColor: "#8fdbfb" // "lightblue"
                backgroundColor: "#4941ae" //  "blue"
                width: 100
                height: 200
                y: - 4*height

                AnimatedLetter {
                    id:anim
                    anchors.fill: parent
                    target: parent
                    type: "YTranslation"
                    yTo: 0
                    duration: 450
                    onEnded: {
                        // Start next letter hen animation is finished
                        // If last letter, then start next animation : QUIZ
                        if( index+1 < weddRepeater.count) wedd.children[index+1].start()
                        else quizAnim.start()
                    }
                }
            }
        }
    }


    SequentialAnimation {
        id: quizAnim
        ScaleAnimator {
            target: quiz
            duration: 500
            from:0
            to:1
        }

        ScaleAnimator {
            target: quiz
            duration: 200
            from:1
            to:0.8
        }
        ScaleAnimator {
            target: quiz
            duration: 150
            from:0.8
            to:1
        }
        onStarted: quiz.visible = true
        onStopped: quiz.children[0].start()
    }

    Row{
        id: quiz
        visible: false
        anchors.top: wedd.bottom
        anchors.horizontalCenter: wedd.horizontalCenter
        Repeater {
            id: quizRepeater
            model:["Q","U","I","Z"]

            delegate: Letter {
                text: modelData
                letterColor: index % 2 == 0 ? "#fdd4d8" : "#f6fbdb" // rouge:ff9090
                backgroundColor: index % 2 == 0 ? "#bf3220" : "#d9ae14"
                width: 100
                height: 200

                function start() {
                    animC.start()
                }

                AnimatedLetter {
                    id:animC
                    anchors.fill: parent
                    target: parent
                    type: "Compression"
                    duration: 450
                    onEnded: if(index+1 < quizRepeater.count) quiz.children[index+1].start()
                }
            }
        }
    }
}
