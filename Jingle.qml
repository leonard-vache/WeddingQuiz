import QtQuick 2.15
import QtMultimedia 5.15

Rectangle {
    id: root

    property int padding: Math.round(width * 0.05)
    property int letterWidth: Math.round((width - 2*padding) / 8)
    property int letterHeight: 2 * letterWidth

    property int spacing: 10

    readonly property int wLetterIndex: 0
    readonly property int qLetterIndex: 9

    property bool weddingLettersVisible: false
    property bool quizLettersVisible: false
    property bool startQuizArrivalAnimation: false
    property bool startFinalAnimation: false

    property real quizFinalLetterScale: 1.2
    property real weddingFinalLetterScale: 0.3

    property bool running: false
    // Inform restoring is in progress
    property bool restoring: false

    signal reset()
    signal start()

    onReset: restore()
    onStart: launch()


    color: "black"

    function restore() {
        restoring = true

        startQuizArrivalAnimation = false
        startFinalAnimation = false
        weddingLettersVisible = false
        quizLettersVisible = false
        running = false
        // Reset Letters
        for(var i = 0; i < root.children.length; ++i ) {
            var child = root.children[i]
            if(child.reset !== undefined)
                child.reset()
        }

        instrum.reset()

        restoring = false
    }

    function launch() {
        root.running = true
        root.children[0].start()
        weddingLettersVisible = true
//        print("launch")
//        audioPresentations.start()
    }


    Repeater {
        id: weddingLetters
        property int offsetX: Math.round(0.5 * (root.width - weddingLetters.count * letterWidth))
        property int offsetY: Math.round(0.5 * (root.height - 2 * letterHeight - root.spacing))

        model:["w","e","d","d","i","n","g"]

        delegate:  Item {
          id: wlContainer

          function reset() {
              wl.reset()
              wlContainer.x = weddingLetters.offsetX + index * letterWidth
              wlContainer.y = weddingLetters.offsetY
              sprite.reset()
          }

          function start() {
                anim.start()
                sprite.reset()
                sound.play()
            }

            width: letterWidth
            height: letterHeight
            x: weddingLetters.offsetX + index * letterWidth
            y: weddingLetters.offsetY

            Letter {
                id: wl

                property int yOutOfWindow: -letterHeight - weddingLetters.offsetY

                function reset() {
                    anim.stop()
                    sound.reset()
                    wl.y= yOutOfWindow
                    wl.yScale = 1.0
                    wl.xScale = 1.0
                }

                visible: weddingLettersVisible
                text: modelData
                letterColor: "#8fdbfb"
                backgroundColor: "#4941ae"
                y: yOutOfWindow
                width: letterWidth
                height: letterHeight

                //////////////////////////////////////////////////////////////////////////////////////
                AnimatedLetter {
                    id: anim
                    anchors.fill: wl
                    target: wl
                    type: "YTranslation"
                    to: 0
                    duration: 550
                    onEnded: {
                        if( restoring == false) {
                            // Start next letter when animation is finished
                            // If last letter, then start next animation : QUIZ
                            if( index+1 < weddingLetters.count) root.children[wLetterIndex+index+1].start()
                            else startQuizArrivalAnimation = true
                        }
                    }

                } // end of AnimatedLetter (id: anim)

                //////////////////////////////////////////////////////////////////////////////////////
                Audio {
                    id: sound
                    source: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/jingle_"+ modelData+".mp3"
                    loops: 1
                    function reset() {
                        stop()
                        seek(0)
                    }
                }

                //////////////////////////////////////////////////////////////////////////////////////
                Connections {
                    target: root
                    function onStartFinalAnimationChanged() {
                        if (startFinalAnimation == true && restoring == false)
                        {
                            var rectSize = weddingFinalLetterScale * letterHeight
                            sprite.visible = false
                            weddingLettersBorder.visible = true
                            wl.yScale = weddingFinalLetterScale
                            wl.xScale = weddingFinalLetterScale * letterHeight / letterWidth
                            wlContainer.x = Math.round((root.width - quizFinalLetterScale * letterHeight * 2) * 0.5) - rectSize
                            wlContainer.y = 0
                            wl.y= Math.round((root.height - rectSize * weddingLetters.count) * 0.5) + index * rectSize
                        }
                    }
                }
            } // end of Letter

            AnimatedSprite {
                id: sprite

                property real letterBottomOffset: letterHeight * 0.1
                property bool yCollision: wl.y + letterHeight >= y + letterBottomOffset
                onYCollisionChanged: if(yCollision === true) restart()

                function reset() {
                    visible = true
                    yCollision = Qt.binding(function() { return  wl.y + letterHeight >= y + letterBottomOffset} )
                    stop()
                    currentFrame = 0
                    loops = loops + 1
                }

                // 1st: binded on y position / 2nd set when final animation starts
                visible: true // wl.y + letterHeight >= y + letterBottomOffset
//                onVisibleChanged: if(visible === true) restart()
                anchors.bottom: parent.bottom
                anchors.bottomMargin: letterBottomOffset
                anchors.horizontalCenter: parent.horizontalCenter
                width: letterWidth * 0.75
                height: width * frameHeight/frameWidth // Keep aspect ratio

                source: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/jingle_cake_sprite_834x962_7_frames.png"
                // On a seulement 6 frames mais cela evite un glitch a la fin de l'animation (comme si la 1er frame était rechargee)
                // La 7e frames est transparente ou identique a la 6e
                frameCount: 7
                frameX: 0
                frameY: 0
                frameWidth: 834
                frameHeight: 962
                loops: 1
                interpolate: true
                frameDuration: 50

                onCurrentFrameChanged: if(currentFrame == frameCount-2) sprite.stop()

            } // end of AnimatedSprite (id: sprite)

            Component.onCompleted: sprite.reset()

        } // end of Item (id: wl)

    } // end of Repeater


    Rectangle {
        id: weddingLettersBorder

        function reset() { visible = false }

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

            function reset()
            {
                ql.yScale = 1.0
                ql.xScale = 1.0
                ql.x = quizLetters.offsetX + letterWidth * index
                ql.y = quizLetters.offsetY
                quizArrivalAnimation.stop()
                animC.stop()
                animS.stop()
                quizFinalAnimation.reset()
            }

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
                function onStartQuizArrivalAnimationChanged() {
                    if(startQuizArrivalAnimation == true)
                    {
                        quizAudio.play()
                        quizArrivalAnimation.start()
                    }
                }

                function onStartFinalAnimationChanged() {
                    if(startFinalAnimation == true && restoring == false)
                    {
                        ql.yScaleOrigin = 0
                        quizFinalAnimation.start()
                    }
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
                onStopped: if(index == 0 && restoring == false) root.children[qLetterIndex].startCompressionAnimation()
            }

            //////////////////////////////////////////////////////////////////////////////////////
            AnimatedLetter {
                id: animC
                anchors.fill: ql
                target: ql
                type: "Compression"
                duration: 450
                onEnded: {
                    if( restoring == false)
                    {
                        if(index+1 < quizLetters.count)
                            root.children[qLetterIndex+index+1].startCompressionAnimation()
                        else
                            startFinalAnimation = true
                    }
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////
            Item {
                id : quizFinalAnimation

                property int duration: 500
                property int rectangularLetterSize: animS.to * letterHeight

                anchors.fill: parent

                function reset()
                {
                    for( var i = 0; i < children.length; i++)
                        quizFinalAnimation.children[i].stop()
                }

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
                    onEnded: if(restoring == false) audioPresentations.start()
                }

            } // end of Item (id: quizFinalAnimation)

        } // end of delegate: Letter (id: ql)

    } // end of Repeater


    ///////////////////////////////////////////////////////////////////////////

    Audio {
        id: quizAudio

        property bool loading: true

        autoLoad : true
        source: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/jingle_quiz.mp3"
        loops: 1

        function reset() {
            stop()
            seek(0)
        }

        onStopped: if(restoring == false && startQuizArrivalAnimation == true) instrum.play()

        // Afin que l'audio soit synchro avec l'annimation on la joue une premiere fois
        // pour que le media soit bufferize et ainsi eviter une latence
        onStatusChanged:
        {
            if(loading == true)
            {
                if(status == Audio.Loaded)
                {
                    volume = 0.0 // Coupe le son pendant la phase de chargement
                    play()
                }

                if(status == Audio.EndOfMedia)
                {
                    reset()
                    volume = 1.0
                    loading = false
                }
            }

        } // end of onStatusChanged

    } // end of Audio (id: quizAudio)


    Audio {
        id: instrum
        source: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/jingle_instrum.mp3"
        loops: Audio.Infinite

        function reset() {
            stop()
            seek(0)
        }
        volume: QtMultimedia.convertVolume(0.4,
                                           QtMultimedia.LogarithmicVolumeScale,
                                           QtMultimedia.LinearVolumeScale)

    } // end of Audio (id:instrum)


    JingleAudioPresentations {
        id: audioPresentations
        onEnded: root.running = false
    }

}


