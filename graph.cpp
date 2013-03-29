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
#include <QDebug>

//ogdf::DPolyline &p = m_attributes.bends(e);
//p.pushBack(ogdf::DPoint(10,20*e->index()));
//p.pushBack(ogdf::DPoint(20*e->index(),10));

Graph::Graph(QObject *parent)
    : QObject(parent),
      m_graph(),
      m_attributes(m_graph, ogdf::GraphAttributes::nodeGraphics |
                   ogdf::GraphAttributes::edgeGraphics),
      m_activeLoops(0),
      m_layout(0),
      m_nodes(&m_attributes),
      m_edges(&m_attributes)
{
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

GraphLayout *Graph::layout() const
{
    return m_layout;
}

void Graph::setLayout(GraphLayout *layout)
{
    if (layout == m_layout) {
        return;
    }
    m_layout = layout;
    emit layoutChanged();
    invalidateLayout();
}

void Graph::randomGraph(int n, int m)
{
    ogdf::randomGraph(m_graph, m, n);
    invalidateLayout();
}

bool Graph::randomSimpleGraph(int n, int m)
{
    bool success = ogdf::randomSimpleGraph(m_graph, n, m);
    invalidateLayout();
    return success;
}

void Graph::randomBiconnectedGraph(int n, int m)
{
    ogdf::randomBiconnectedGraph(m_graph, m, n);
    invalidateLayout();
}

void Graph::randomTriconnectedGraph(int n, double p1, double p2)
{
    ogdf::randomTriconnectedGraph(m_graph, n, p1, p2);
    invalidateLayout();
}

void Graph::randomTree(int n)
{
    ogdf::randomTree(m_graph, n);
    invalidateLayout();
}

void Graph::randomTree(int n, int maxDeg, int maxWidth)
{
    ogdf::randomTree(m_graph, n, maxDeg, maxWidth);
    invalidateLayout();
}

void Graph::randomHierarchy(int n, int m, bool planar,
                            bool singleSource, bool longEdges)
{
    ogdf::randomHierarchy(m_graph, n, m, planar,
                          singleSource, longEdges);
    invalidateLayout();
}

void Graph::randomDiGraph(int n, double p)
{
    ogdf::randomDiGraph(m_graph, n, p);
    invalidateLayout();
}

int Graph::addNode(QJSValue attributes)
{
    ogdf::node v = m_graph.newNode();
    setNodeAttributes(v, attributes);
    invalidateLayout();
    return v->index();
}

void Graph::eachNode(QJSValue callback)
{
    if (callback.isCallable()) {
        QJSValueList arguments;
        arguments << QJSValue();
        ogdf::node v;
        m_activeLoops++;
        forall_nodes (v, m_graph) {
            arguments[0] = v->index();
            callback.call(arguments);
        }
        m_activeLoops--;
        if (!m_layoutValid) {
            invalidateLayout();
        }
    } else {
        qCritical() << "Expected function as first argument";
    }
}

void Graph::modifyNode(int index, QJSValue setter)
{
    ogdf::node v = m_nodes.node(index);
    if (!v) {
        qWarning() << "Can not modify node with index" << index;
        return;
    }
    if (setter.isObject()) {
        setNodeAttributes(v, setter);
        invalidateLayout();
    } else if (setter.isCallable()) {
        QJSValueList arguments;
        arguments << QJSValue(nodeAttributes(v));
        setNodeAttributes(v, setter.call(arguments));
        invalidateLayout();
    } else {
        qCritical() << "Expected object or function as second argument";
    }
}

void Graph::removeNode(int index)
{
    ogdf::node v = m_nodes.node(index);
    if (!v) {
        qWarning() << "Can not remove node with index" << index;
    } else {
        m_graph.delNode(v);
        invalidateLayout();
    }
}

int Graph::addEdge(int sourceNode, int targetNode)
{
    ogdf::node v1 = m_nodes.node(sourceNode);
    ogdf::node v2 = m_nodes.node(targetNode);
    if (!v1 || !v2) {
        qWarning() << "One node index does not exist";
        return -1;
    } else {
        ogdf::edge e = m_graph.newEdge(v1, v2);
        invalidateLayout();
        return e->index();
    }
}

void Graph::eachEdge(QJSValue callback)
{
    if (callback.isCallable()) {
        QJSValueList arguments;
        arguments << QJSValue();
        ogdf::edge e;
        m_activeLoops++;
        forall_edges (e, m_graph) {
            arguments[0] = e->index();
            callback.call(arguments);
        }
        m_activeLoops--;
        if (!m_layoutValid) {
            invalidateLayout();
        }
    } else {
        qCritical() << "Expected function(index) as first argument";
    }
}

void Graph::removeEdge(int index)
{
    ogdf::edge e = m_edges.edge(index);
    if (!e) {
        qWarning() << "Can not remove egde with index" << index;
    } else {
        m_graph.delEdge(e);
        invalidateLayout();
    }
}

void Graph::clear()
{
    m_graph.clear();
}

void Graph::invalidateLayout()
{
    m_layoutValid = false;
    if (m_layout && m_activeLoops == 0) {
        m_layout->call(m_attributes);
        m_nodes.attributesChanged();
        m_edges.attributesChanged();
        m_layoutValid = true;
    }
}

QJSValue Graph::nodeAttributes(ogdf::node v)
{
    QJSValue object;
    object.setProperty("x", m_attributes.x(v));
    object.setProperty("y", m_attributes.y(v));
    object.setProperty("width", m_attributes.width(v));
    object.setProperty("height", m_attributes.height(v));
    return object;
}

void Graph::setNodeAttributes(ogdf::node v, QJSValue object)
{
    m_attributes.x(v) = object.property("x").toNumber();
    m_attributes.y(v) = object.property("y").toNumber();
    m_attributes.width(v) = object.property("width").toNumber();
    m_attributes.height(v) = object.property("height").toNumber();
    m_attributes.shapeNode(v) = ogdf::GraphAttributes::rectangle;
}
