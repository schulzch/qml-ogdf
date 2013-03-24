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

Rectangle {
    id: container
    width: 800
    height: 600
    color: "white"
    GraphTools {
        id: graphTools
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: 150
    }
    CanvasView {
        id: canvasView
        anchors.top: parent.top
        anchors.left: graphTools.right
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        GraphScene {
            id: graphScene
        }
    }
}
