import QtQuick 2.14

Item {
    id: container

    property variant target
    property int duration: 1000
    property int yTo: 0
    // YTranslation  |  Compression
    property string type: "YTranslation"

    function start() {
        if( container.type === "YTranslation")
            yTranslationAnimation.start()
        else if (container.type === "Compression")
            compressAnimation.start()
    }

    signal ended()

    PropertyAnimation {
        id: yTranslationAnimation
        target: container.target
        property: "y"
        duration: container.duration
        from: target.y
        to: container.yTo
        onStopped: container.ended()
    }

    SequentialAnimation {
        id: compressAnimation
        PropertyAnimation {
            target: container.target
//            property: "height"
            property: "yScale"
            duration: container.duration * 0.6
            from: target.yScale
            to: target.yScale * 0.6
        }

        PropertyAnimation {
            target: container.target
            property: "yScale"
            duration: container.duration * 0.1
            from: target.yScale * 0.6
            to: target.yScale
        }

        PropertyAnimation {
            target: container.target
            property: "yScale"
            duration: container.duration * 0.15
            from: target.yScale
            to: target.yScale * 0.85
        }

        PropertyAnimation {
            target: container.target
            property: "yScale"
            duration: container.duration * 0.15
            from: target.yScale * 0.85
            to: target.yScale
        }

        onStopped: container.ended()
    }
}
