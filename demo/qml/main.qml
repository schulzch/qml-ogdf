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
    color: "#272822"
    Timer {
        interval: 0
        running: true
        repeat: false
        onTriggered: {
            // Setup initial state (the hackish way).
            graphTools.model.execute(0);
        }
    }
    Graph {
        id: graph
        layout: GraphLayout {

        }
    }
    GraphTools {
        id: graphTools
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 150
        model: ListModel {
            ListElement { caption: "Random" }
            ListElement { caption: "Random/Simple" }
            ListElement { caption: "Random/Biconnected" }
            ListElement { caption: "Random/Triconnected" }
            ListElement { caption: "Random/Tree/N" }
            ListElement { caption: "Random/Tree/Width" }
            ListElement { caption: "Random/Hierarchy" }
            ListElement { caption: "Random/DiGraph" }
            ListElement { caption: "Iterate/Nodes" }
            ListElement { caption: "Iterate/Edges" }
            ListElement { caption: "Layout (HACK)" }
            function execute(index) {
                var n = 10;
                var m = 20;
                var p = 0.618;
                switch (index) {
                case 0:
                    graph.clear();
                    graph.randomGraph(n, m);
                    break;
                case 1:
                    graph.clear();
                    graph.randomSimpleGraph(n, m);
                    break;
                case 2:
                    graph.clear();
                    graph.randomBiconnectedGraph(n, m);
                    break;
                case 3:
                    graph.clear();
                    graph.randomTriconnectedGraph(n, p, 1.0 - p);
                    break;
                case 4:
                    graph.clear();
                    graph.randomTree(n);
                    break;
                case 5:
                    graph.clear();
                    graph.randomTree(n, n / 2.0, graphView.width);
                    break;
                case 6:
                    graph.clear();
                    graph.randomHierarchy(n, m, true, false, true);
                    break;
                case 7:
                    graph.clear();
                    graph.randomDiGraph(n, p);
                    break;
                case 8:
                    consoleView.text = "Iterating nodes...\n";
                    graph.eachNode(function(index) {
                        consoleView.text += " " + index;
                    });
                    consoleView.text += "\n...done!\n";
                    consoleView.visible = true;
                    break;
                case 9:
                    consoleView.text = "Iterating edges...\n ";
                    graph.eachEdge(function(index) {
                        consoleView.text += " " + index;
                    });
                    consoleView.text += "\n...done!\n";
                    consoleView.visible = true;
                    break;
                case 10:
                    graph.layout.layout = GraphLayout.SugiyamaLayout
                    break;
                default:
                    console.log("NYI: execute " + index.toString());
                }
                // Assign size to every node.
                graph.eachNode(function(index) {
                    graph.modifyNode(index, { width: 50, height: 20 });
                });
                //var left = graph.addNode();
                //var bottom = graphView.graph.addNode();
                //graphView.graph.addEdge(left, bottom);
                //console.log("Adding nodes " + left + " and " + bottom + " along with an edge");
            }
        }
    }
    Rectangle {
        id: graphToolsBorder
        width: 1
        anchors.top: parent.top
        anchors.right: graphTools.left
        anchors.bottom: parent.bottom
        color: "#22231d"
    }
    GraphView {
        id: graphView
        anchors.top: parent.top
        anchors.right: graphToolsBorder.left
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
            color: "#ffffff"
        }
        Text {
            id: edgeCount
            anchors.top: nodeCount.bottom
            anchors.left: parent.left
            text: "Edges: " + graph.edges.count
            color: "#ffffff"
        }
    }
    ConsoleView {
        id: consoleView
        anchors.fill: parent
        visible: false
    }
}
