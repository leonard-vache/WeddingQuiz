import QtQuick 2.14

Item {
    id: container
    property variant target
    property int duration: 1000
    property variant to: 0
    // YTranslation | YTranslation | RectangularScale | Compression
    property string type: "YTranslation"

    function start() {
        if( container.type === "YTranslation")
            yTranslationAnimation.start()
        else if( container.type === "XTranslation")
            xTranslationAnimation.start()
        else if (container.type === "RectangularScale")
            rectScaleAnimation.start()
        else if (container.type === "Compression")
            compressAnimation.start()
    }

    signal ended()

    PropertyAnimation {
        id: xTranslationAnimation
        target: container.target
        property: "x"
        duration: container.duration
        from: target.x
        to: container.to
        onStopped: container.ended()
    }

    PropertyAnimation {
        id: yTranslationAnimation
        target: container.target
        property: "y"
        duration: container.duration
        from: target.y
        to: container.to
        onStopped: container.ended()
    }

//    ParallelAnimation {
//        id: rectScaleAnimation

//        PropertyAnimation {
//            target: container.target
//            property: "height"
//            from: container.target.height
//            to: container.target.height * container.to
//            duration: container.duration
//        }

//        PropertyAnimation {
//            target: container.target
//            property: "width"
//            from: container.target.width
//            to: container.target.height * container.to
//            duration: container.duration
//        }
//        onStopped: container.ended()
//    }

    ParallelAnimation {
        id: rectScaleAnimation

        PropertyAnimation {
            target: container.target
            property: "yScale"
            from: container.target.yScale
            to: container.to
            duration: container.duration
        }

        PropertyAnimation {
            target: container.target
            property: "xScale"
            from: container.target.yScale
            to: container.to * container.target.height  / container.target.width
            duration: container.duration
        }
        onStopped: container.ended()
    }



//    ScaleAnimator {
//        id: scaleAnimation
//        target: container.target
//        from: 1.0
//        to: container.to
//        duration: container.duration
//        onStopped: container.ended()
//    }

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
