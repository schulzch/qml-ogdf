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

function random(index) {
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
    default:
        return;
    }
    // Assign size to every node.
    graph.eachNode(function(index) {
        graph.modifyNode(index, { width: 50, height: 20 });
    });
}

function iterator(index) {
    switch (index) {
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
    }
}

function layout(index) {
    switch (index) {
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
    }
}
