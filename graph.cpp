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
#include "graph.h"
#include "ogdf/basic/graph_generators.h"
#include "ogdf/energybased/FMMMLayout.h"
#include <QDebug>

//m_attributes.x(v) = options.value("x", 0.0f).toDouble();
//m_attributes.y(v) = options.value("y", 0.0f).toDouble();
//m_attributes.width(v) = options.value("width", 0.0f).toDouble();
//m_attributes.height(v) = options.value("height", 0.0f).toDouble();
//m_attributes.shapeNode(v) = ogdf::GraphAttributes::rectangle;

//ogdf::DPolyline &p = m_attributes.bends(e);
//p.pushBack(ogdf::DPoint(10,20*e->index()));
//p.pushBack(ogdf::DPoint(20*e->index(),10));

Graph::Graph(QObject *parent)
    : QObject(parent), m_graph(),
      m_attributes(m_graph, ogdf::GraphAttributes::nodeGraphics |
                   ogdf::GraphAttributes::edgeGraphics),
      m_nodes(&m_attributes), m_edges(&m_attributes)
{
    // Do nothing.
}

Graph::~Graph()
{
}

NodeModel *Graph::nodes()
{
    return &m_nodes;
}

EdgeModel *Graph::edges()
{
    return &m_edges;
}

void Graph::randomGraph(int n, int m)
{
    return ogdf::randomGraph(m_graph, m, n);
}

bool Graph::randomSimpleGraph(int m, int n)
{
    return ogdf::randomSimpleGraph(m_graph, m, n);
}

void Graph::randomBiconnectedGraph(int n, int m)
{
    return ogdf::randomBiconnectedGraph(m_graph, m, n);
}

void Graph::randomTriconnectedGraph(int n, double p1, double p2)
{
    return ogdf::randomTriconnectedGraph(m_graph, n, p1, p2);
}

void Graph::randomTree(int n)
{
    return ogdf::randomTree(m_graph, n);
}

void Graph::randomTree(int n, int maxDeg, int maxWidth)
{
    return ogdf::randomTree(m_graph, n, maxDeg, maxWidth);
}

void Graph::randomHierarchy(int n, int m, bool planar,
                            bool singleSource, bool longEdges)
{
    return ogdf::randomHierarchy(m_graph, n, m, planar,
                                 singleSource, longEdges);
}

void Graph::randomDiGraph(int n, double p)
{
    return ogdf::randomDiGraph(m_graph, n, p);
}

int Graph::addNode()
{
    return m_graph.newNode()->index();
}

void Graph::eachNode(QJSValue callback)
{
    if (callback.isCallable()) {
        QJSValueList arguments;
        arguments << QJSValue();
        ogdf::node v;
        forall_nodes (v, m_graph) {
            arguments[0] = v->index();
            callback.call(arguments);
        }
    } else {
        qCritical() << "Expected function(index) as first argument";
    }
}

void Graph::removeNode(int index)
{
    bool found = false;
    ogdf::node v;
    forall_nodes (v, m_graph) {
        if (v->index() == index) {
            m_graph.delNode(v);
            found = true;
            break;
        }
    }
    if (!found) {
        qWarning() << "Can not remove node with index" << index;
    }
}

int Graph::addEdge(int sourceNode, int targetNode)
{
    bool found1 = false;
    ogdf::node v1;
    forall_nodes (v1, m_graph) {
        if (v1->index() == sourceNode) {
            found1 = true;
            break;
        }
    }
    bool found2 = false;
    ogdf::node v2;
    forall_nodes (v2, m_graph) {
        if (v2->index() == targetNode) {
            found2 = true;
            break;
        }
    }
    if (found1 && found2) {
        ogdf::edge e = m_graph.newEdge(v1, v2);
        return e->index();
    } else {
        return -1;
    }
}

void Graph::eachEdge(QJSValue callback)
{
    if (callback.isCallable()) {
        QJSValueList arguments;
        arguments << QJSValue();
        ogdf::edge e;
        forall_edges (e, m_graph) {
            arguments[0] = e->index();
            callback.call(arguments);
        }
    } else {
        qCritical() << "Expected function(index) as first argument";
    }
}

void Graph::removeEdge(int index)
{
    bool found = false;
    ogdf::edge e;
    forall_edges (e, m_graph) {
        if (e->index() == index) {
            m_graph.delEdge(e);
            found = true;
            break;
        }
    }
    if (!found) {
        qWarning() << "Can not remove egde with index" << index;
    }
}

void Graph::clear()
{
    m_graph.clear();
}

void Graph::fmmmLayout()
{
    ogdf::FMMMLayout fmmm;
    fmmm.useHighLevelOptions(true);
    fmmm.unitEdgeLength(15.0);
    fmmm.newInitialPlacement(true);
    fmmm.qualityVersusSpeed(ogdf::FMMMLayout::qvsGorgeousAndEfficient);
    fmmm.call(m_attributes);
    m_nodes.attributesChanged();
    m_edges.attributesChanged();
}
