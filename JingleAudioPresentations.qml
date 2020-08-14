import QtQuick 2.15
import QtMultimedia 5.15


Item {
    id: root

    property bool restoring: false
    property int firstPhotoIndex: 0
    signal ended()

    function start() {
        audio.play()
        firstPhotoTimer.start()
    }

    function reset() {
        restoring = true

        audio.reset()
        firstPhotoTimer.stop()

        restoring = false
    }


    Audio {
        id: audio

        function reset() { stop(); seek(0) }

        objectName: "Audio"
        source: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/jingle_presentations.mp3"
        loops: 1
        onStopped: if (restoring == false) ended()

    } // end of Audio


    Timer {
        id: firstPhotoTimer
        interval: 12000
        repeat: false
        onTriggered:
        {
            root.children[firstPhotoIndex].start()
        }
    }

    ListModel {
        id: photoPresentationModel
        ListElement {
            photo: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/presentation_camille.jpg"
            duree: 9000
            x: 760
            y: 340
            width: 400
            height: 400
        }

        ListElement {
            photo: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/presentation_romain.jpg"
            duree: 10500
            x: 760
            y: 340
            width: 400
            height: 400
        }

        ListElement {
            photo: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/presentation_nina.jpeg"
            duree: 10000
            x: 540
            y: 80
            width: 340
            height: 340
        }

        ListElement {
            photo: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/presentation_margaux.jpg"
            duree: 8000
            x: 540
            y: 590
            width: 340
            height: 340
        }
        ListElement {
            photo: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/presentation_delphine.jpg"
            duree: 9000
            x: 1050
            y: 75
            width: 340
            height: 340
        }

        ListElement {
            photo: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/presentation_diane.jpg"
            duree: 7000
            x: 1050
            y: 600
            width: 340
            height: 340
        }
        ListElement {
            photo: "file:///C:/Users/vache/Documents/GitHub/WeddingQuiz/resources/presentation_leo_charles.jpg"
            duree: 10000
            x: 760
            y: 340
            width: 400
            height: 400
        }
    }

    Repeater
    {
        id: photoPresenter
        model:photoPresentationModel

        delegate: Item {
            id: presentation

            function start() {
                img.visible = true
                imgTimer.start()
                scaleAnim.start()
            }

            function stop() {
                img.visible = false
                imgTimer.stop()
                scaleAnim.stop()
            }

            x: model.x
            y: model.y

            Image {
                id: img
                visible: false
                source:  model.photo
                fillMode: Image.PreserveAspectFit
                width: model.width
                height: model.height

                ScaleAnimator {
                    id: scaleAnim
                    target: img
                    duration: 700
                    from: 0
                    to: 1
                }
            }

            Timer {
                id: imgTimer
                interval: model.duree
                repeat: false
                onTriggered: {
                    presentation.stop()
                    if( index+1 < photoPresenter.count) root.children[firstPhotoIndex+index+1].start()
                }

            }

        }
    }

}
