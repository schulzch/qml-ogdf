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
        property color lineColor: "#22231d"
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
        x: childrenRect.width < view.width ? (view.width - childrenRect.width) / 2 : -childrenRect.x * 2
        y: childrenRect.height < view.height ? (view.height - childrenRect.height) / 2 : -childrenRect.y * 2
        width: childrenRect.width
        height: childrenRect.height
    }
}
