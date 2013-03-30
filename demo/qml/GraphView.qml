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
import OGDF 1.0

CanvasView {
    id: graphView
    property QtObject graph: null
    clip: true
    Item {
        id: graphScene
        x: childrenRect.x
        y: childrenRect.y
        width: childrenRect.width
        height: childrenRect.height
        Repeater {
            model: graphView.graph.edges
            delegate: Canvas {
                property int sourceX: model.sourceX
                property int sourceY: model.sourceY
                property int targetX: model.targetX
                property int targetY: model.targetY
                property int minX: Math.min(sourceX, targetX)
                property int minY: Math.min(sourceY, targetY)
                property int maxX: Math.max(sourceX, targetX)
                property int maxY: Math.max(sourceY, targetY)
                x: minX
                y: minY
                width: maxX - minX
                height: maxY - minY
                renderTarget: Canvas.Image
                antialiasing: true
                onPaint: {
                    var context = getContext('2d');
                    context.strokeStyle = '#ffffff';
                    context.lineWidth = 1;
                    context.beginPath();
                    context.moveTo(sourceX - x, sourceY - y);
                    for (var bend in model.bends) {
                        //context.lineTo(bend.x - x, bend.y - y);
                    }
                    context.lineTo(targetX - x, targetY - y);
                    context.stroke();
                }
                Behavior on sourceX {
                    NumberAnimation {
                        duration: 500
                    }
                }
                Behavior on sourceY {
                    NumberAnimation {
                        duration: 500
                    }
                }
                Behavior on targetX {
                    NumberAnimation {
                        duration: 500
                    }
                }
                Behavior on targetY {
                    NumberAnimation {
                        duration: 500
                    }
                }
            }
        }
        Repeater {
            model: graphView.graph.nodes
            delegate: Rectangle {
                x: model.x - model.width / 2
                y: model.y - model.height / 2
                width: model.width
                height: model.height
                color: "#49483e"
                radius: 4
                border.width: 1
                border.color: "#af9476"
                Behavior on x {
                    NumberAnimation {
                        duration: 500
                    }
                }
                Behavior on y {
                    NumberAnimation {
                        duration: 500
                    }
                }
                Text {
                    anchors.centerIn: parent
                    color: "#ffffff"
                    text: model.index
                }
            }
        }
    }
}
