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

Rectangle {
    id: container
    width: 800
    height: 600
    color: "white"
    Graph {
        id: graph
    }
    GraphTools {
        id: graphTools
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 150
        model: ListModel {
            ListElement { caption: "Random/Simple" }
            ListElement { caption: "NYI: More" }
            ListElement { caption: "NYI: Menu-Items" }
            function execute(index) {
                if (index !== 0) {
                    console.log("NYI: execute " + index);
                    return;
                }
                graph.clear();
                graph.randomSimpleGraph(10, 20);
                graph.eachNode(function(index) {
                    //console.log("test" + index);
                });
                var left = graph.addNode();
                // var bottom = graphView.graph.addNode(10, 10, 50, 50);
                // graphView.graph.addEdge(left, bottom);
                //console.log("Adding nodes " + left + " and " + bottom + " along with an edge");
                graph.fmmmLayout();
            }
        }
    }
    GraphView {
        id: graphView
        anchors.top: parent.top
        anchors.right: graphTools.left
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        graph: graph
    }
    Item {
        id: graphStats
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 2
        Text {
            id: nodeCount
            anchors.top: parent.top
            anchors.left: parent.left
            text: "Nodes: " + graph.nodes.count
        }
        Text {
            id: edgeCount
            anchors.top: nodeCount.bottom
            anchors.left: parent.left
            text: "Edges: " + graph.edges.count
        }
    }
}
