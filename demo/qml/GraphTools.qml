/*
 * Copyright (c) 2013 Christoph Schulz
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details: http://www.gnu.org/copyleft/lesser
 */
import QtQuick 2.0

ShaderEffect {
    id: background
    property real time: 1.0
    property point resolution: Qt.point(width, height)
    width: 200
    height: 40
    fragmentShader:
        "uniform highp vec2 resolution;" +
        "uniform highp float time;" +
        "const highp float size = 50.0;" +
        "const int num = 84;" +
        "void main() {" +
        "  highp float sum = 0.0;" +
        "  for (int i = 0; i < num; i++) {" +
        "    highp vec2 position = resolution / 2.0;" +
        "    position.x += sin(time / 3.0 + 1.0 * float(i)) * resolution.x * 0.25;" +
        "    position.y += tan(time / 5.0 + (2.0 + sin(time) * 0.01) * float(i)) * resolution.y * 0.25;" +
        "    sum += size / length(gl_FragCoord.xy - position);" +
        "  }" +
        "  gl_FragColor = vec4(vec3(sum / float(num)), 1.0);" +
        "}"
    NumberAnimation on time {
        loops: Animation.Infinite;
        from: 0;
        to: 1.0;
        duration: 2000
    }
    Text {
        id: ogdfLabel
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 6
        font.family: "Arial,Verdana,sans-serif"
        font.pixelSize: 30
        font.letterSpacing: 10
        font.bold: true
        color: "#ffffff"
        text: "OGDF"
    }
    Text {
        id: forQMLLabel
        anchors.right: ogdfLabel.right
        anchors.top: ogdfLabel.bottom
        font.family: "Arial,Verdana,sans-serif"
        font.pixelSize: 15
        font.letterSpacing: 5
        font.bold: true
        color: "#ffffff"
        text: "for QML"
    }
    ListView {
        id: menuView
        anchors.top: forQMLLabel.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        height: 14
        model: [qsTr("NYI:"), qsTr("Some"), qsTr("Useful"), qsTr("Menu-Items")]
        currentIndex: -1
        boundsBehavior: Flickable.StopAtBounds
        spacing: 6
        delegate: Rectangle {
            width: childrenRect.width
            height: childrenRect.height
            radius: 4
            color: menuView.currentIndex == index ? "#cc666666" : "#cc333333"
            Text {
                width: paintedWidth
                font.family: "Arial,Verdana,sans-serif"
                font.pixelSize: 16
                color: "white"
                text: modelData
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        console.log("NYI: selected " + index);
                    }
                    onEntered: {
                        menuView.focus = true;
                        menuView.currentIndex = index;
                    }
                    onExited: {
                        menuView.currentIndex = -1;
                    }
                }
            }
        }
    }
}
