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

Item {
    id: container
    x: childrenRect.x
    y: childrenRect.y
    width: childrenRect.width
    height: childrenRect.height
    Graph {
        id: graph
    }
    Text {
        id: nodeCount
        anchors.top: parent.top
        anchors.right: parent.right
        text: "Nodes: #" + graph.nodes.count
    }
    Text {
        id: edgeCount
        anchors.top: nodeCount.bottom
        anchors.right: parent.right
        text: "Edges: #" + graph.edges.count
    }
    Text {
        anchors.centerIn: parent
        text: "Click to add nodes"
        visible: graph.nodes.count === 0
    }
    Text {
        anchors.centerIn: parent
        text: "Click to add nodes"
        visible: graph.nodes.count === 0
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            graph.clear();
            graph.randomSimpleGraph(10, 20);
            graph.eachNode(function(index) {
                console.log("test" + index);
            });
            var left = graph.addNode();
            // var bottom = graph.addNode(10, 10, 50, 50);
            // graph.addEdge(left, bottom);
            //console.log("Adding nodes " + left + " and " + bottom + " along with an edge");
            graph.fmmmLayout();
        }
    }
    Repeater {
        model: graph.edges
        delegate: Canvas {
            anchors.fill: parent
            renderTarget: Canvas.Image
            antialiasing: true
            onPaint: {
                var context = getContext('2d');
                context.strokeStyle = '#555';
                context.lineWidth = 1.5;
                context.beginPath();
                context.moveTo(model.sourceX, model.sourceY);
                for (var bend in model.bends) {
                    context.lineTo(bend.x, bend.y);
                }
                context.lineTo(model.targetX, model.targetY);
                context.stroke();
            }
        }
    }
    Repeater {
        model: graph.nodes
        delegate: Rectangle {
            x: model.x
            y: model.y
            width: model.width
            height: model.height
            color: "gray"
            radius: 4
            border.width: 1
            border.color: "black"
            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: model.index
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    graph.removeNode(model.index);
                }
            }
        }
    }

}
