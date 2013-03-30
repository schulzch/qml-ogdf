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
#include <QJSValue>
#include "nodemodel.h"
#include "edgemodel.h"
#include "graphlayout.h"
#include "ogdf/basic/Graph.h"
#include "ogdf/basic/GraphAttributes.h"

/**
 * @brief The Graph class
 */
class Graph : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GraphLayout *layout READ layout CONSTANT)
    Q_PROPERTY(NodeModel *nodes READ nodes CONSTANT)
    Q_PROPERTY(EdgeModel *edges READ edges CONSTANT)
public:
    Graph(QObject *parent = 0);
    ~Graph();

    NodeModel *nodes();
    EdgeModel *edges();

    GraphLayout *layout() const;

    Q_INVOKABLE void randomGraph(int n, int m);
    Q_INVOKABLE bool randomSimpleGraph(int n, int m);
    Q_INVOKABLE void randomBiconnectedGraph(int n, int m);
    Q_INVOKABLE void randomTriconnectedGraph(int n, double p1, double p2);
    Q_INVOKABLE void randomTree(int n);
    Q_INVOKABLE void randomTree(int n, int maxDeg, int maxWidth);
    Q_INVOKABLE void randomHierarchy(int n, int m, bool planar,
                                     bool singleSource, bool longEdges);
    Q_INVOKABLE void randomDiGraph(int n, double p);

    Q_INVOKABLE int addNode(QJSValue attributes);
    Q_INVOKABLE void eachNode(QJSValue callback);
    Q_INVOKABLE void modifyNode(int index, QJSValue setter);
    Q_INVOKABLE void removeNode(int index);

    Q_INVOKABLE int addEdge(int sourceNode, int targetNode);
    Q_INVOKABLE void eachEdge(QJSValue callback);
    Q_INVOKABLE void removeEdge(int index);

    Q_INVOKABLE void clear();

private slots:
    void invalidateLayout();

private:
    Q_DISABLE_COPY(Graph)
    QJSValue nodeAttributes(ogdf::node v);
    void setNodeAttributes(ogdf::node v, QJSValue object);

    ogdf::Graph m_graph;
    ogdf::GraphAttributes m_attributes;
    int m_activeLoops;
    bool m_layoutValid;
    QScopedPointer<GraphLayout> m_layout;
    NodeModel m_nodes;
    EdgeModel m_edges;
};

#endif
