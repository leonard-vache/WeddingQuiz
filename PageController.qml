import QtQuick 2.14

Item {
    id: control

    ScorePage {
        visible: scorePage.showed
        anchors.fill: parent
    }

    Jingle {
        visible: jinglePage.showed
        width: window.width
        height: window.height
        onRunningChanged: if(running) visible = true
    }

}
