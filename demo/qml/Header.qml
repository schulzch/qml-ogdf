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
    property color startColor: "#030131"
    property color endColor: "#6b3252"
    width: 200
    height: 40
    fragmentShader:
        "varying highp vec2 qt_TexCoord0;" +
        "uniform highp vec4 startColor;" +
        "uniform highp vec4 endColor;" +
        "void main() {" +
        "  lowp float t = length(vec2(qt_TexCoord0.x * qt_TexCoord0.x, " +
        "      qt_TexCoord0.x + 0.2));" +
        "  gl_FragColor = startColor + (endColor - startColor) * t;" +
        "}"
    Text {
        id: ogdfLabel
        anchors.left: parent.left
        anchors.leftMargin: 6
        anchors.verticalCenter: parent.verticalCenter
        font.family: "Arial,Verdana,sans-serif"
        font.pixelSize: 30
        font.bold: true
        color: "#ffffff"
        text: "OGDF"
    }
    Text {
        id: forQMLLabel
        anchors.left: ogdfLabel.right
        anchors.baseline: ogdfLabel.baseline
        font.family: "Arial,Verdana,sans-serif"
        font.pixelSize: 15
        font.bold: true
        color: "#ffffff"
        text: "for QML"
    }
    /*
    ListView {
        id: menuView
        anchors.left: forQMLLabel.right
        anchors.right: parent.right
        anchors.bottom: forQMLLabel.baseline
        height: 14
        model: [qsTr("NYI:"), qsTr("Some"), qsTr("Useful"), qsTr("Menu-Items")]
        currentIndex: -1
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        spacing: 6
        delegate: Text {
            width: paintedWidth
            font.family: "Arial,Verdana,sans-serif"
            font.pixelSize: 16
            color: menuView.currentIndex == index ? "#ffffff" : "#0088CC"
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
    }*/
}
