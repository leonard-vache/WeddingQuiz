import QtQuick 2.14

Item {
    id: root

    property string fontName: "HooliganJF"
    property int fontSize: 85
    property alias heading: header.text
    property alias title: title.text
    property int headingAvailableWidth: root.width


    Text {
        id: title
        padding: 10
        anchors.horizontalCenter: root.horizontalCenter
        anchors.top: root.top
        anchors.topMargin: fontSize * 0.5
        width: headingAvailableWidth
        text: "Is this a Question ?"
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        font.family: fontName
        font.pixelSize: fontSize
    }


    Text {
        id: header
        padding: 10
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter
        width: root.width
        text: "Is this a Question ?"
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        font.family: fontName
        font.pixelSize: fontSize * 1.2
    }
}
