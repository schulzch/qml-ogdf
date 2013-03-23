import QtQuick 2.0

Rectangle {
    id: container
    width: 800
    height: 600
    color: "white"
    Header {
        id: header
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40
    }
    CanvasView {
        id: canvasView
        anchors.left: parent.left
        anchors.top: header.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        GraphView {
            id: graphView
        }
    }
}
