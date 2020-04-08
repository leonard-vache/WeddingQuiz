import QtQuick 2.14

Rectangle {
    id: root

    property int padding: Math.round(width * 0.05)
    property int letterWidth: Math.round((width - 2*padding) / 8)
    property int letterHeight: 2 * letterWidth
    property bool weddingLettersVisible: false
    property bool quizLettersVisible: false
    property int spacing: 10

    readonly property int wLetterIndex: 0
    readonly property int dLetterIndex: 2
    readonly property int qLetterIndex: 9

    property bool startQuizArrivalAnimation: false
    property bool startFinalAnimation: false

    property real quizFinalLetterScale: 1.2
    property real weddingFinalLetterScale: 0.3

    property bool running: false


    color: "black"

    function start() {
        root.running = true
        root.children[0].start()
        weddingLettersVisible = true
    }


    Repeater {
        id: weddingLetters

        property int offsetX: Math.round(0.5 * (root.width - weddingLetters.count * letterWidth))
        property int offsetY: Math.round(0.5 * (root.height - 2 * letterHeight - root.spacing))

        model:["w","e","d","d","i","n","g"]

        delegate: Letter {
            id: wl

            function start() {
                anim.start()
            }

            visible: weddingLettersVisible
            text: modelData
            letterColor: "#8fdbfb"
            backgroundColor: "#4941ae"
            width: letterWidth
            height: letterHeight
            x: weddingLetters.offsetX + index * letterWidth
            y: - 4*height


            //////////////////////////////////////////////////////////////////////////////////////
            AnimatedLetter {
                id: anim
                anchors.fill: parent
                target: wl
                type: "YTranslation"
                to: weddingLetters.offsetY
                duration: 450
                onEnded: {
                    // Start next letter when animation is finished
                    // If last letter, then start next animation : QUIZ
                    if( index+1 < weddingLetters.count) root.children[wLetterIndex+index+1].start()
                    else startQuizArrivalAnimation = true
                }

            } // end of AnimatedLetter (id: anim)

            //////////////////////////////////////////////////////////////////////////////////////
            Connections {
                target: root
                onStartFinalAnimationChanged: {
                    var rectSize = weddingFinalLetterScale * letterHeight
                    weddingLettersBorder.visible = true
                    wl.yScale = weddingFinalLetterScale
                    wl.xScale = weddingFinalLetterScale * letterHeight / letterWidth
                    wl.x = Math.round((root.width - quizFinalLetterScale * letterHeight * 2) * 0.5) - rectSize
                    wl.y= Math.round((root.height - rectSize * weddingLetters.count) * 0.5) + index * rectSize
                }
            }
        } // end of Letter

    } // end of Repeater


    Rectangle {
        id: weddingLettersBorder
        visible: false
        color: "transparent"
        x: Math.round((root.width - quizFinalLetterScale * letterHeight * 2) * 0.5) - weddingFinalLetterScale * letterHeight - border.width
        y: Math.round((root.height - weddingFinalLetterScale * letterHeight * weddingLetters.count) * 0.5) - border.width
        height: weddingLetters.count * weddingFinalLetterScale * letterHeight + 2*border.width
        width: weddingFinalLetterScale * letterHeight + 2*border.width
        radius: 5

        border.color: "lightblue"
        border.width: 15
    }


    Repeater {
        id: quizLetters

        property int offsetX: Math.round(0.5 * (root.width - quizLetters.count * letterWidth))
        property int offsetY: weddingLetters.offsetY + letterHeight + root.spacing

        model:["q","u","i","z"]

        delegate: Letter {
            id: ql
            visible: quizLettersVisible
            x: quizLetters.offsetX + letterWidth * index
            y: quizLetters.offsetY
            yScaleOrigin: height
            text: modelData
            letterColor: index % 2 == 0 ? "#fdd4d8" : "#f6fbdb" // rouge:ff9090
            backgroundColor: index % 2 == 0 ? "#bf3220" : "#d9ae14"
            width: letterWidth
            height: letterHeight

            function startCompressionAnimation() {
                animC.start()
            }

            Connections {
                target: root
                onStartQuizArrivalAnimationChanged: quizArrivalAnimation.start()
                onStartFinalAnimationChanged: {
                    ql.yScaleOrigin = 0
                    quizFinalAnimation.start()
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////
            SequentialAnimation {
                id: quizArrivalAnimation

                ScaleAnimator {
                    target: ql
                    duration: 500
                    from: 0
                    to: 1
                }

                ScaleAnimator {
                    target: ql
                    duration: 200
                    from: 1
                    to: 0.8
                }
                ScaleAnimator {
                    target: ql
                    duration: 150
                    from: 0.8
                    to: 1
                }
                onStarted: quizLettersVisible = true
                onStopped: if(index == 0) root.children[qLetterIndex].startCompressionAnimation()
            }

            //////////////////////////////////////////////////////////////////////////////////////
            AnimatedLetter {
                id: animC
                anchors.fill: ql
                target: ql
                type: "Compression"
                duration: 450
                onEnded: {
                    if(index+1 < quizLetters.count)
                        root.children[qLetterIndex+index+1].startCompressionAnimation()
                    else
                        startFinalAnimation = true
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////
            Item {
                id : quizFinalAnimation

                property int duration: 500
                property int rectangularLetterSize: animS.to * letterHeight

                anchors.fill: parent

                function start() {
                    for( var i = 0; i < children.length; i++)
                        quizFinalAnimation.children[i].start()
                }

                AnimatedLetter {
                    anchors.fill: parent
                    target: ql
                    type: "YTranslation"
                    to: index < 2 ?  Math.round((root.height - quizFinalAnimation.rectangularLetterSize * 2) * 0.5)
                                  :  Math.round((root.height - quizFinalAnimation.rectangularLetterSize * 2) * 0.5 + quizFinalAnimation.rectangularLetterSize)
                    duration: quizFinalAnimation.duration
                }

                AnimatedLetter {
                    anchors.fill: parent
                    target: ql
                    type: "XTranslation"
                    to: index % 2 ? Math.round((root.width - quizFinalAnimation.rectangularLetterSize * 2) * 0.5 + quizFinalAnimation.rectangularLetterSize)
                                  : Math.round((root.width - quizFinalAnimation.rectangularLetterSize * 2) * 0.5)
                    duration: quizFinalAnimation.duration
                }

                AnimatedLetter {
                    id: animS
                    anchors.fill: parent
                    target: ql
                    type: "RectangularScale"
                    to: quizFinalLetterScale
                    duration: quizFinalAnimation.duration
                    onEnded: root.running = false
                }

            } // end of Item (id: quizFinalAnimation)

        } // end of delegate: Letter (id: ql)

    } // end of Repeater

}


