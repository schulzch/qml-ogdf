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
                    graph.layout.algorithm = GraphLayout.BalloonLayout;
                    break;
                case 11:
                    graph.layout.algorithm = GraphLayout.CircularLayout;
                    break;
                case 12:
                    graph.layout.algorithm = GraphLayout.ComponentSplitterLayout;
                    break;
                case 13:
                    graph.layout.algorithm = GraphLayout.DavidsonHarelLayout;
                    break;
                case 14:
                    graph.layout.algorithm = GraphLayout.DominanceLayout;
                    break;
                case 15:
                    graph.layout.algorithm = GraphLayout.FMMMLayout;
                    break;
                case 16:
                    graph.layout.algorithm = GraphLayout.FPPLayout;
                    break;
                case 17:
                    graph.layout.algorithm = GraphLayout.FastMultipoleEmbedder;
                    break;
                case 18:
                    graph.layout.algorithm = GraphLayout.FastMultipoleMultilevelEmbedder;
                    break;
                case 19:
                    graph.layout.algorithm = GraphLayout.GEMLayout;
                    break;
                case 20:
                    graph.layout.algorithm = GraphLayout.MMMExampleFastLayout;
                    break;
                case 21:
                    graph.layout.algorithm = GraphLayout.MMMExampleNiceLayout;
                    break;
                case 22:
                    graph.layout.algorithm = GraphLayout.MMMExampleNoTwistLayout;
                    break;
                case 23:
                    graph.layout.algorithm = GraphLayout.MixedForceLayout;
                    break;
                case 24:
                    graph.layout.algorithm = GraphLayout.MixedModelLayout;
                    break;
                case 25:
                    graph.layout.algorithm = GraphLayout.ModularMultilevelMixer;
                    break;
                case 26:
                    graph.layout.algorithm = GraphLayout.MultilevelLayout;
                    break;
                case 27:
                    graph.layout.algorithm = GraphLayout.PlanarDrawLayout;
                    break;
                case 28:
                    graph.layout.algorithm = GraphLayout.PlanarStraightLayout;
                    break;
                case 29:
                    graph.layout.algorithm = GraphLayout.PlanarizationGridLayout;
                    break;
                case 30:
                    graph.layout.algorithm = GraphLayout.PlanarizationLayout;
                    break;
                case 31:
                    graph.layout.algorithm = GraphLayout.PreprocessorLayout;
                    break;
                case 32:
                    graph.layout.algorithm = GraphLayout.RadialTreeLayout;
                    break;
                case 33:
                    graph.layout.algorithm = GraphLayout.ScalingLayout;
                    break;
                case 34:
                    graph.layout.algorithm = GraphLayout.SchnyderLayout;
                    break;
                case 35:
                    graph.layout.algorithm = GraphLayout.SpringEmbedderFR;
                    break;
                case 36:
                    graph.layout.algorithm = GraphLayout.SpringEmbedderFRExact;
                    break;
                case 37:
                    graph.layout.algorithm = GraphLayout.SpringEmbedderKK;
                    break;
                case 38:
                    graph.layout.algorithm = GraphLayout.StressMajorization;
                    break;
                case 39:
                    graph.layout.algorithm = GraphLayout.SugiyamaLayout;
                    break;
                case 40:
                    graph.layout.algorithm = GraphLayout.TreeLayout;
                    break;
                case 41:
                    graph.layout.algorithm = GraphLayout.TutteLayout;
                    break;
                case 42:
                    graph.layout.algorithm = GraphLayout.UpwardPlanarizationLayout;
                    break;
                case 43:
                    graph.layout.algorithm = GraphLayout.VisibilityLayout;
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
