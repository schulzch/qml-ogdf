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
    var n = (Math.random() * 10 + 5) | 0;
    var m = Math.max(n + 1, (Math.random() * n * (n - 1) / 2) | 0);
    var p = 0.618;
    switch (index) {
    case 0:
        graph.randomGraph(n, m);
        break;
    case 1:
        graph.randomSimpleGraph(n, m);
        break;
    case 2:
        graph.randomBiconnectedGraph(n, m);
        break;
    case 3:
        graph.randomTriconnectedGraph(n, p, 1.0 - p);
        break;
    case 4:
        graph.randomTree(n);
        break;
    case 5:
        graph.randomTree(n, n / 2.0, graphView.width);
        break;
    case 6:
        graph.randomHierarchy(n, m, true, false, true);
        break;
    case 7:
        graph.randomDiGraph(n, p);
        break;
    default:
        return;
    }
}

function layout(index) {
    switch (index) {
    case 0:
        graph.layout.algorithm = GraphLayout.BalloonLayout;
        break;
    case 1:
        graph.layout.algorithm = GraphLayout.CircularLayout;
        break;
    case 2:
        graph.layout.algorithm = GraphLayout.ComponentSplitterLayout;
        break;
    case 3:
        graph.layout.algorithm = GraphLayout.DavidsonHarelLayout;
        break;
    case 4:
        graph.layout.algorithm = GraphLayout.DominanceLayout;
        break;
    case 5:
        graph.layout.algorithm = GraphLayout.FMMMLayout;
        break;
    case 6:
        graph.layout.algorithm = GraphLayout.FPPLayout;
        break;
    case 7:
        graph.layout.algorithm = GraphLayout.FastMultipoleEmbedder;
        break;
    case 8:
        graph.layout.algorithm = GraphLayout.FastMultipoleMultilevelEmbedder;
        break;
    case 9:
        graph.layout.algorithm = GraphLayout.GEMLayout;
        break;
    case 10:
        graph.layout.algorithm = GraphLayout.MMMExampleFastLayout;
        break;
    case 11:
        graph.layout.algorithm = GraphLayout.MMMExampleNiceLayout;
        break;
    case 12:
        graph.layout.algorithm = GraphLayout.MMMExampleNoTwistLayout;
        break;
    case 13:
        graph.layout.algorithm = GraphLayout.MixedForceLayout;
        break;
    case 14:
        graph.layout.algorithm = GraphLayout.MixedModelLayout;
        break;
    case 15:
        graph.layout.algorithm = GraphLayout.ModularMultilevelMixer;
        break;
    case 16:
        graph.layout.algorithm = GraphLayout.MultilevelLayout;
        break;
    case 17:
        graph.layout.algorithm = GraphLayout.PlanarDrawLayout;
        break;
    case 18:
        graph.layout.algorithm = GraphLayout.PlanarStraightLayout;
        break;
    case 19:
        graph.layout.algorithm = GraphLayout.PlanarizationGridLayout;
        break;
    case 20:
        graph.layout.algorithm = GraphLayout.PlanarizationLayout;
        break;
    case 21:
        graph.layout.algorithm = GraphLayout.PreprocessorLayout;
        break;
    case 22:
        graph.layout.algorithm = GraphLayout.RadialTreeLayout;
        break;
    case 23:
        graph.layout.algorithm = GraphLayout.ScalingLayout;
        break;
    case 24:
        graph.layout.algorithm = GraphLayout.SchnyderLayout;
        break;
    case 25:
        graph.layout.algorithm = GraphLayout.SpringEmbedderFR;
        break;
    case 26:
        graph.layout.algorithm = GraphLayout.SpringEmbedderFRExact;
        break;
    case 27:
        graph.layout.algorithm = GraphLayout.SpringEmbedderKK;
        break;
    case 28:
        graph.layout.algorithm = GraphLayout.StressMajorization;
        break;
    case 29:
        graph.layout.algorithm = GraphLayout.SugiyamaLayout;
        break;
    case 30:
        graph.layout.algorithm = GraphLayout.TreeLayout;
        break;
    case 31:
        graph.layout.algorithm = GraphLayout.TutteLayout;
        break;
    case 32:
        graph.layout.algorithm = GraphLayout.UpwardPlanarizationLayout;
        break;
    case 33:
        graph.layout.algorithm = GraphLayout.VisibilityLayout;
        break;
    }
}
