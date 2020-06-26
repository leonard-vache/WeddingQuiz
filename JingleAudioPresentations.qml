import QtQuick 2.15
import QtMultimedia 5.15


Item {
    id: root

    property bool restoring: false
    signal ended()

    function start() {
        children[0].play()
    }

    function reset() {
        restoring = true
        presentations.reset()
        restoring = false
    }

    Repeater {
        id: presentations
        function reset() {
            for(var i = 0; i < root.children.length; ++i ) {
                root.children[i].reset()
            }
        }

        model: ["intro", "camille", "romain", "margaux", "diane", "nina", "delphine", "leo_charles"]
        delegate: Item {
            function play() { audio.play() }
            function reset() { audio.stop(); audio.seek(0) }

            Audio {
                id: audio
                source: "resources/jingle_" + modelData + ".mp3"
                loops: 1
                onStopped: {
                    if(restoring === false)
                    {
                        if( index+1 < presentations.count) root.children[index+1].play()
                        else ended()
                    }
                }

            } // end of Audio
        }

    } // end of Repeater (id: presentations)
}
