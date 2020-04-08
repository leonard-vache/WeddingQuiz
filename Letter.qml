import QtQuick 2.14

//Rectangle {
//    border.width: 1
//    border.color: "green"
//    color: "transparent"
Item {
    id: container

    property real xScale: 1
    property real yScale: 1
    property int xScaleOrigin: 0
    property int yScaleOrigin: 0
    property alias text: label.text
    property color letterColor: "white"
    property color backgroundColor: "black"



    Rectangle {
        color: letterColor
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -Math.round(height/2)
        width: label.text == "w"
               ? Math.round(label.contentWidth * 0.77)
               : Math.round(label.contentWidth * 0.67)
        height: Math.round(label.contentHeight * 0.4)
    }

    Rectangle {
        color: letterColor
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: Math.round(height/2) - 1
        width: Math.round(label.contentWidth * 0.67)
        height: Math.round(label.contentHeight * 0.26)
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

    transform: Scale { origin.x: xScaleOrigin; origin.y: container.yScaleOrigin; xScale: container.xScale; yScale: container.yScale }
}
