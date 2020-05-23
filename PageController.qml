import QtQuick 2.14

Item {
    id: control

    property bool startJingle: jinglePage.run
    onStartJingleChanged: if(startJingle === true) jingle.start()

    ScorePage {
        visible: scorePage.showed
        anchors.fill: parent
    }

    Jingle {
        id: jingle
        visible: jinglePage.showed
        width: window.width
        height: window.height
        onRunningChanged: if(running == false) jinglePage.run = false
    }

}
