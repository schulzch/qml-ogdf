import QtQuick 2.0

Rectangle {
    property alias text: textBuffer.text

    id: consoleView
    anchors.fill: parent
    color: "#d8323232"
    onVisibleChanged: {
        if (consoleView.visible) {
            textBuffer.focus = true;
            textBuffer.cursorPosition = textBuffer.text.length
        }
    }
    Keys.onEscapePressed: {
        consoleView.visible = false;
    }
    MouseArea {
        anchors.fill: parent
        preventStealing: true
        hoverEnabled: true
        onClicked: {
            consoleView.visible = false;
        }
    }
    Rectangle {
        id: textBackground
        anchors.centerIn: parent
        width: 480
        height: parent.height * 0.8
        color: "#272822"
        radius: 6
        clip: true
        TextEdit {
            id: textBuffer
            anchors.fill: parent
            anchors.margins: 6
            font.family: "Arial,Verdana,sans-serif"
            font.pixelSize: 12
            wrapMode: TextEdit.WrapAnywhere
            selectedTextColor: "#ffffff"
            selectionColor: "#49483e"
            color: "#ffffff"
            selectByMouse: true
            readOnly: true
        }
    }
    Text {
        anchors.left: textBackground.right
        anchors.top: textBackground.bottom
        anchors.right: textBackground.left
        horizontalAlignment: Text.AlignHCenter
        font.family: "Arial,Verdana,sans-serif"
        font.pixelSize: 12
        font.bold: true
        color: "#e6db74"
        text: qsTr("Press escape to hide.")
    }
}
