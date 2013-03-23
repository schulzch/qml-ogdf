import QtQuick 2.0

Flickable {
    default property alias innerData: viewInner.data
    property int panStep: 15

    id: view
    contentWidth: Math.max(width, viewInner.width)
    contentHeight: Math.max(height, viewInner.height)
    focus: parent.visible
    Keys.onUpPressed:  {
        contentY = Math.max(contentY - panStep, 0)
    }
    Keys.onDownPressed: {
        contentY = Math.min(contentY + panStep,
                            contentHeight - height)
    }
    Keys.onLeftPressed:  {
        contentX = Math.max(contentX - panStep, 0)
    }
    Keys.onRightPressed: {
        contentX = Math.min(contentX + panStep,
                            contentWidth - width)
    }
    Behavior on contentX {
        NumberAnimation {
            duration: 45
        }
    }
    Behavior on contentY {
        NumberAnimation {
            duration: 45
        }
    }
    ShaderEffect {
        id: background
        property real spacing: 4.0
        property color lineColor: "#e3e3e3"
        property color color: "transparent"
        anchors.fill: parent
        fragmentShader:
            "uniform lowp float spacing;" +
            "uniform lowp vec4 lineColor;" +
            "uniform lowp vec4 color;" +
            "void main() {" +
            "  if (mod(gl_FragCoord.x + gl_FragCoord.y, spacing) == 0.0) {" +
            "    gl_FragColor = lineColor;" +
            "  } else {" +
            "    gl_FragColor = color;" +
            "  }" +
            "}"
    }
    Item {
        id: viewInner
        x: -childrenRect.x
        y: -childrenRect.y
        width: childrenRect.width
        height: childrenRect.height
    }
}
