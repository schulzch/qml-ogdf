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
import "main.js" as Controller

Rectangle {
    id: container
    width: 1024
    height: 768
    color: "#272822"
    Graph {
        id: graph
    }
    Timer {
        id: autoLayouter
        interval: 100
        repeat: true
        running: true
        onTriggered: {
            graph.layout.call();
        }
    }
    Sidebar {
        id: sidebar
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        selectedIndex: 0
        actionModel: ListModel {
            ListElement { caption: "Random" }
            ListElement { caption: "Simple" }
            ListElement { caption: "Biconnected" }
            ListElement { caption: "Triconnected" }
            ListElement { caption: "Tree/N" }
            ListElement { caption: "Tree/Width" }
            ListElement { caption: "Hierarchy" }
            ListElement { caption: "DiGraph" }
            function execute(index) {
                Controller.random(index);
            }
        }
        layoutModel: ListModel {
            ListElement { caption: "Balloon" }
            ListElement { caption: "Circular" }
            ListElement { caption: "ComponentSplitter" }
            ListElement { caption: "DavidsonHarel" }
            ListElement { caption: "Dominance" }
            ListElement { caption: "FMMM" }
            ListElement { caption: "FPP" }
            ListElement { caption: "FME" }
            ListElement { caption: "FMME" }
            ListElement { caption: "GEM" }
            ListElement { caption: "MMMExampleFast" }
            ListElement { caption: "MMMExampleNice" }
            ListElement { caption: "MMMExampleNoTwist" }
            ListElement { caption: "MixedForce" }
            ListElement { caption: "MixedModel" }
            ListElement { caption: "ModularMultilevelMixer" }
            ListElement { caption: "Multilevel" }
            ListElement { caption: "PlanarDraw" }
            ListElement { caption: "PlanarStraight" }
            ListElement { caption: "PlanarizationGrid" }
            ListElement { caption: "Planarization" }
            ListElement { caption: "Preprocessor" }
            ListElement { caption: "RadialTree" }
            ListElement { caption: "Scaling" }
            ListElement { caption: "Schnyder" }
            ListElement { caption: "SpringEmbedderFR" }
            ListElement { caption: "SpringEmbedderFRExact" }
            ListElement { caption: "SpringEmbedderKK" }
            ListElement { caption: "StressMajorization" }
            ListElement { caption: "Sugiyama" }
            ListElement { caption: "Tree" }
            ListElement { caption: "Tutte" }
            ListElement { caption: "UpwardPlanarization" }
            ListElement { caption: "Visibility" }
            function execute(index) {
                Controller.layout(index);
            }
        }

    }
    Rectangle {
        id: sidebarBorder
        width: 1
        anchors.top: parent.top
        anchors.right: sidebar.left
        anchors.bottom: parent.bottom
        color: "#22231d"
    }
    CanvasView {
        anchors.top: parent.top
        anchors.right: sidebarBorder.left
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        clip: true
        GraphView {
            property var highlightedNode: null
            property var highlightedEdge: null
            id: graphView
            anchors.fill: parent
            model: graph
            edgeDelegate: EdgeSpline {
                color: model.edge === graphView.highlightedEdge ? "#ff0000" : "#ffffff"
            }
            nodeDelegate: Rectangle {
                id: rect
                width: childrenRect.width + 8
                height: childrenRect.height + 4
                color: "#49483e"
                radius: 4
                border.width: 1
                border.color: "#af9476"
                Text {
                    x: 4
                    y: 2
                    font.pixelSize: 12
                    color: model.node === graphView.highlightedNode ? "#ff0000" : "#ffffff"
                    text: model.node
                }
            }
        }
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
    Timer {
        property int nodeIndex: 0
        property int edgeIndex: 0
        id: highlightTimer
        interval: 100
        repeat: true
        running: true
        onTriggered: {
            if (nodeIndex < graph.nodes.count) {
                graphView.highlightedNode = graph.nodes.get(nodeIndex);
                graphView.highlightedEdge = null;
                nodeIndex++;
            } else if (edgeIndex < graph.edges.count) {
                graphView.highlightedNode = null;
                graphView.highlightedEdge = graph.edges.get(edgeIndex);
                edgeIndex++;
            } else {
                graphView.highlightedNode = null;
                graphView.highlightedEdge = null;
                nodeIndex = 0;
                edgeIndex = 0;
            }
        }
    }
}
