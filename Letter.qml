import QtQuick 2.9

Item {
    id: container

    property real xScale: 1
    property real yScale: 1
    property alias text: label.text
    property color letterColor: "white"
    property color backgroundColor: "black"

    Rectangle {
        color: letterColor
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -Math.round(height/2)
        width: Math.round(label.contentWidth * 0.74)
        height: Math.round(label.contentHeight * 0.4)
    }

    Rectangle {
        color: letterColor
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: Math.round(height/2) - 1
        width: Math.round(label.contentWidth * 0.67)
        height: Math.round(label.contentHeight * 0.25)
    }

    Text {
        id: label
        anchors.fill: parent
        text: "A"
        color: backgroundColor
        font.family: "Horseshoes And Lemonade"
        fontSizeMode: Text.Fit; minimumPixelSize: 10; font.pixelSize: 1000
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter
    }

    transform: Scale { origin.x: Math.round(width/2); origin.y: height; xScale: container.xScale; yScale: container.yScale }
}
