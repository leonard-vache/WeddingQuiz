import QtQuick 2.15
import QtMultimedia 5.15
import WeddingQuiz 1.0

Item {
    id: root

    property string source: ""
    property bool running: false

    property bool isVideo: false
    property bool isImage: false
    property int autopause: -1
    property bool autopauseDone: false
    // From C++ Model
    signal reset()
    signal play()
    signal pause()
    // To C++ model
    signal stopped()
    signal positionChanged(int pos)

    enabled: source !== ""

    Video {
        id: video

        enabled: root.isVideo
        anchors.fill: parent
        source: isVideo ? root.source : ""
        notifyInterval: 200

        Connections {
            target: root

            function onPlay() { video.play() }
            function onPause() { video.pause() }
            function onReset() { video.seek(0) }
        }

        onStopped: root.stopped();
        onPositionChanged: {
            if( autopause > 0 && autopauseDone == false && position > autopause) {
                video.pause()
                autopauseDone = true
            }
        }
    }

    Image {
        id: img
        source: isImage ? root.source : ""
        enabled: root.isImage
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        onVisibleChanged: if(visible==false) root.stopped()
    }

}
