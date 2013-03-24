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
#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include "nodemodel.h"
#include "edgemodel.h"
#include "ogdf/basic/Graph.h"
#include "ogdf/basic/GraphAttributes.h"

/**
 * @brief The Graph class
 */
class Graph : public QObject
{
    Q_OBJECT
    Q_PROPERTY(NodeModel *nodes READ nodes CONSTANT)
    Q_PROPERTY(EdgeModel *edges READ edges CONSTANT)
public:
    Graph(QObject *parent = 0);
    ~Graph();

    NodeModel *nodes();
    EdgeModel *edges();

    Q_INVOKABLE void randomSimpleGraph(int nodeCount, int edgeCount);

    Q_INVOKABLE int addNode(double x, double y, double width, double height);
    Q_INVOKABLE void removeNode(int index);

    Q_INVOKABLE int addEdge(int sourceNode, int targetNode);
    Q_INVOKABLE void removeEdge(int index);

    Q_INVOKABLE void clear();

    Q_INVOKABLE void fmmmLayout();

private:
    Q_DISABLE_COPY(Graph)

    ogdf::Graph m_graph;
    ogdf::GraphAttributes m_attributes;
    NodeModel m_nodes;
    EdgeModel m_edges;
};

#endif
