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
#include "ogdf/fileformats/GraphIO.h"
#include <QQmlInfo>

Graph::Graph(QObject *parent)
    : QObject(parent), m_graph(), m_nodeModel(this), m_edgeModel(this),
      m_attributes(m_graph), m_layout(new GraphLayout(m_attributes, this))
{
    connect(m_layout.data(), &GraphLayout::validChanged,
            this, &Graph::updateModels);
}

QUrl Graph::source() const
{
    return m_source;
}

void Graph::setSource(const QUrl &source)
{
    if (source != m_source) {
        m_source = source;
        reload();
        emit sourceChanged();
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

ogdf::GraphAttributes &Graph::attributes()
{
    return m_attributes;
}

bool Graph::save(const QUrl &url)
{
    if (!url.isLocalFile()) {
        qmlInfo(this) << "URL is not a local file";
        return false;
    }
    const char *filename = m_source.toLocalFile().toLatin1().data();
    bool result = ogdf::GraphIO::writeGML(m_attributes, filename);
    if (result && m_source != url) {
        m_source = url;
        emit sourceChanged();
    }
    return result;
}

bool Graph::reload()
{
    if (!m_source.isLocalFile()) {
        qmlInfo(this) << "Source is not a local file";
        return false;
    }
    clear();
    const char *filename = m_source.toLocalFile().toLatin1().data();
    return ogdf::GraphIO::readGML(m_attributes, m_graph, filename);
}

void Graph::randomGraph(int n, int m)
{
    clear();
    ogdf::randomGraph(m_graph, m, n);
    m_layout->invalidate();
}

void Graph::randomSimpleGraph(int n, int m)
{
    clear();
    if (ogdf::randomSimpleGraph(m_graph, n, m)) {
        m_layout->invalidate();
    } else {
        qmlInfo(this) << "Can not generate a simple graph with "
                      << n << " nodes and " << m << " edges";
    }
}

void Graph::randomBiconnectedGraph(int n, int m)
{
    clear();
    ogdf::randomBiconnectedGraph(m_graph, m, n);
    m_layout->invalidate();
}

void Graph::randomTriconnectedGraph(int n, double p1, double p2)
{
    clear();
    ogdf::randomTriconnectedGraph(m_graph, n, p1, p2);
    m_layout->invalidate();
}

void Graph::randomTree(int n)
{
    clear();
    ogdf::randomTree(m_graph, n);
    m_layout->invalidate();
}

void Graph::randomTree(int n, int maxDeg, int maxWidth)
{
    clear();
    ogdf::randomTree(m_graph, n, maxDeg, maxWidth);
    m_layout->invalidate();
}

void Graph::randomHierarchy(int n, int m, bool planar,
                            bool singleSource, bool longEdges)
{
    clear();
    ogdf::randomHierarchy(m_graph, n, m, planar,
                          singleSource, longEdges);
    m_layout->invalidate();
}

void Graph::randomDiGraph(int n, double p)
{
    clear();
    ogdf::randomDiGraph(m_graph, n, p);
    m_layout->invalidate();
}

void Graph::clear()
{
    m_graph.clear();
}

void Graph::updateModels()
{
    if (m_layout->valid()) {
        m_nodeModel.attributesChanged();
        m_edgeModel.attributesChanged();
    }
}
