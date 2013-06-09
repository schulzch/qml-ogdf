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
    GraphTools {
        id: graphTools
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        selectedIndex: 2
        model: ListModel {
            ListElement { caption: "Iterate" }
            ListElement { caption: "Random" }
            ListElement { caption: "Random/Simple" }
            ListElement { caption: "Random/Biconnected" }
            ListElement { caption: "Random/Triconnected" }
            ListElement { caption: "Random/Tree/N" }
            ListElement { caption: "Random/Tree/Width" }
            ListElement { caption: "Random/Hierarchy" }
            ListElement { caption: "Random/DiGraph" }
            ListElement { caption: "Layout/Balloon" }
            ListElement { caption: "Layout/Circular" }
            ListElement { caption: "Layout/ComponentSplitter" }
            ListElement { caption: "Layout/DavidsonHarel" }
            ListElement { caption: "Layout/Dominance" }
            ListElement { caption: "Layout/FMMM" }
            ListElement { caption: "Layout/FPP" }
            ListElement { caption: "Layout/FME" }
            ListElement { caption: "Layout/FMME" }
            ListElement { caption: "Layout/GEM" }
            ListElement { caption: "Layout/MMMExampleFast" }
            ListElement { caption: "Layout/MMMExampleNice" }
            ListElement { caption: "Layout/MMMExampleNoTwist" }
            ListElement { caption: "Layout/MixedForce" }
            ListElement { caption: "Layout/MixedModel" }
            ListElement { caption: "Layout/ModularMultilevelMixer" }
            ListElement { caption: "Layout/Multilevel" }
            ListElement { caption: "Layout/PlanarDraw" }
            ListElement { caption: "Layout/PlanarStraight" }
            ListElement { caption: "Layout/PlanarizationGrid" }
            ListElement { caption: "Layout/Planarization" }
            ListElement { caption: "Layout/Preprocessor" }
            ListElement { caption: "Layout/RadialTree" }
            ListElement { caption: "Layout/Scaling" }
            ListElement { caption: "Layout/Schnyder" }
            ListElement { caption: "Layout/SpringEmbedderFR" }
            ListElement { caption: "Layout/SpringEmbedderFRExact" }
            ListElement { caption: "Layout/SpringEmbedderKK" }
            ListElement { caption: "Layout/StressMajorization" }
            ListElement { caption: "Layout/Sugiyama" }
            ListElement { caption: "Layout/Tree" }
            ListElement { caption: "Layout/Tutte" }
            ListElement { caption: "Layout/UpwardPlanarization" }
            ListElement { caption: "Layout/Visibility" }
            function execute(index) {
                if (index === 0) {
                    Controller.iterate();
                } else if (index - 1 <= 7) {
                    Controller.random(index - 1);
                } else {
                    Controller.layout(index - 8);
                }
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
