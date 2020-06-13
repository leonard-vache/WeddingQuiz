import QtQuick 2.14
import QtMultimedia 5.14
import WeddingQuiz 1.0

Item {
    id: root

    property string source: ""
    property bool running: false

    property bool isVideo: false
    property bool isImage: false
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

        Connections {
            target: root

            onPlay: video.play()
            onPause: video.pause()
            onReset: video.seek(0)
        }

        onStopped: root.stopped();
        onPositionChanged: {print("position:", position); root.positionChanged(position)}
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
