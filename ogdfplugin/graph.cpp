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
#include <QQmlInfo>

Graph::Graph(QObject *parent)
    : QObject(parent), m_graph(), m_attributes(m_graph), m_autoLayout(true),
      m_layoutLock(0), m_layoutValid(false), m_layout(new GraphLayout()),
      m_nodeModel(this), m_edgeModel(this)
{
    connect(m_layout.data(), &GraphLayout::algorithmChanged,
            this, &Graph::invalidateLayout);
}

bool Graph::autoLayout() const
{
    return m_autoLayout;
}

void Graph::setAutoLayout(bool autoLayout)
{
    if (autoLayout != m_autoLayout) {
        m_autoLayout = autoLayout;
        if (m_autoLayout) {
            m_layoutLock--;
        } else {
            m_layoutLock++;
        }
        emit autoLayoutChanged();
        invalidateLayout();
    }
}

GraphLayout *Graph::layout() const
{
    return m_layout.data();
}

NodeModel *Graph::nodes()
{
    return &m_nodeModel;
}

EdgeModel *Graph::edges()
{
    return &m_edgeModel;
}

ogdf::Graph &Graph::g()
{
    return m_graph;
}

ogdf::GraphAttributes &Graph::attributes()
{
    return m_attributes;
}

ogdf::node Graph::v(const QString &node) const
{
    return m_vs.value(node);
}

QString Graph::node(ogdf::node v) const
{
    return m_nodes[v];
}

void Graph::insertNode(ogdf::node v, const QString &node)
{
    Q_ASSERT(!m_vs.contains(node));
    m_nodes[v] = node;
    m_vs[node] = v;
}

void Graph::removeNode(ogdf::node v)
{
    m_nodes.remove(v);
    m_vs.remove(m_vs.key(v));
}

void Graph::clearNodes()
{
    m_nodes.clear();
    m_vs.clear();
}

ogdf::edge Graph::e(const QString &edge) const
{
    return m_es.value(edge);
}

QString Graph::edge(ogdf::edge e) const
{
    return m_edges[e];
}

void Graph::insertEdge(ogdf::edge e, const QString &edge)
{
    Q_ASSERT(!m_es.contains(edge));
    m_edges[e] = edge;
    m_es[edge] = e;
}

void Graph::removeEdge(ogdf::edge e)
{
    m_edges.remove(e);
    m_es.remove(m_es.key(e));
}

void Graph::clearEdges()
{
    m_edges.clear();
    m_es.clear();
}

void Graph::randomGraph(int n, int m)
{
    clear();
    ogdf::randomGraph(m_graph, m, n);
    invalidateLayout();
}

void Graph::randomSimpleGraph(int n, int m)
{
    clear();
    if (ogdf::randomSimpleGraph(m_graph, n, m)) {
        invalidateLayout();
    } else {
        qmlInfo(this) << "Can not generate a simple graph with "
                      << n << " nodes and " << m << " edges";
    }
}

void Graph::randomBiconnectedGraph(int n, int m)
{
    clear();
    ogdf::randomBiconnectedGraph(m_graph, m, n);
    invalidateLayout();
}

void Graph::randomTriconnectedGraph(int n, double p1, double p2)
{
    clear();
    ogdf::randomTriconnectedGraph(m_graph, n, p1, p2);
    invalidateLayout();
}

void Graph::randomTree(int n)
{
    clear();
    ogdf::randomTree(m_graph, n);
    invalidateLayout();
}

void Graph::randomTree(int n, int maxDeg, int maxWidth)
{
    clear();
    ogdf::randomTree(m_graph, n, maxDeg, maxWidth);
    invalidateLayout();
}

void Graph::randomHierarchy(int n, int m, bool planar,
                            bool singleSource, bool longEdges)
{
    clear();
    ogdf::randomHierarchy(m_graph, n, m, planar,
                          singleSource, longEdges);
    invalidateLayout();
}

void Graph::randomDiGraph(int n, double p)
{
    clear();
    ogdf::randomDiGraph(m_graph, n, p);
    invalidateLayout();
}

void Graph::clear()
{
    m_graph.clear();
}

void Graph::invalidateLayout()
{
    m_layoutValid = false;
    if (m_layout && m_layoutLock == 0) {
        m_layout->call(m_attributes);
        m_nodeModel.attributesChanged();
        m_edgeModel.attributesChanged();
        m_layoutValid = true;
    }
}
