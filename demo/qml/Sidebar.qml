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
    property real time: 1.0
    property point location: Qt.point(x, y)
    property point size: Qt.point(width, height)
    property alias model: menuView.model
    property alias selectedIndex: menuView.selectedIndex

    id: background
    width: 275
    fragmentShader:
        "uniform highp vec2 location;" +
        "uniform highp vec2 size;" +
        "uniform highp float time;" +
        "const highp float TWOPI = 6.28318530717958647693;" +
        "const int NUM = 200;" +
        "void main() {" +
        "  highp float sum = 0.0;" +
        "  highp float s = size.x / 800.0;" +
        "  for (int i = 0; i < NUM; i++) {" +
        "    highp vec2 position = size / 2.0;" +
        "    highp float t = float(i) / float(NUM) * TWOPI + time;" +
        "    position.x += sin(9.0 * t) * size.x * 0.35;" +
        "    position.y += sin(7.0 * t) * size.y * 0.48;" +
        "    sum += s / length(gl_FragCoord.xy - position - location);" +
        "  }" +
        "  highp float value =  pow(sum, 2.0);" +
        "  gl_FragColor = vec4(value * 0.5, value * 0.7, value, value);" +
        "}"
    NumberAnimation on time {
        loops: Animation.Infinite;
        from: 0.0
        to: 2.0 * Math.PI
        duration: 80000
    }
    Text {
        id: ogdfLabel
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 25
        font.family: "Arial,Verdana,sans-serif"
        font.pixelSize: 30
        font.letterSpacing: 10
        font.bold: true
        color: "#ffffff"
        text: "OGDF"
    }
    Text {
        id: forQMLLabel
        anchors.top: ogdfLabel.bottom
        anchors.right: ogdfLabel.right
        font.family: "Arial,Verdana,sans-serif"
        font.bold: true
        font.pixelSize: 15
        font.letterSpacing: 5
        color: "#ffffff"
        text: "for QML"
    }
    ListView {
        id: menuView
        property bool hovering: false
        property int selectedIndex: -1
        anchors.top: forQMLLabel.bottom
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        height: 14
        currentIndex: -1
        boundsBehavior: Flickable.StopAtBounds
        spacing: 6
        clip: true
        delegate: Text {
            x: 6
            width: menuView.width - 12
            font.family: "Arial,Verdana,sans-serif"
            font.bold: menuView.selectedIndex == index
            font.pixelSize: 12
            color: menuView.selectedIndex == index ? "#ffffff" : "#66ffffff"
            text: "» " + model.caption
            clip: true
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    menuView.selectedIndex = index;
                }
                onEntered: {
                    menuView.hovering = true;
                    menuView.focus = true;
                    menuView.currentIndex = index;
                }
                onExited: {
                    menuView.hovering = false;
                }
            }
        }
        highlight: Rectangle {
            x: 3
            width: menuView.width - 6
            height: 20
            radius: 3
            color: "#66666666"
        }
        onCurrentIndexChanged: {
            if (!hovering) {
                selectedIndex = currentIndex;
            }
        }
        onSelectedIndexChanged: {
            model.execute(selectedIndex);
            currentIndex = selectedIndex;
        }
        onModelChanged: {
            model.execute(selectedIndex);
            currentIndex = selectedIndex;
        }
        Item {
            id: scrollArea
            anchors.right: parent.right
            anchors.rightMargin: 2
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 2
            height: parent.height
            clip: true
            Rectangle {
                x: 0
                y: menuView.visibleArea.yPosition * parent.height
                height: menuView.visibleArea.heightRatio * parent.height
                width: parent.width
                color: "#99999999"
            }
        }
    }
}
