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
#include "edgemodel.h"
#include "graph.h"
#include <QQmlInfo>
#include <QPointF>

EdgeModel::EdgeModel(Graph *graph)
    : QAbstractListModel(graph), ogdf::GraphObserver(&graph->g()),
      m_graph(graph)
{
    m_roles[Qt::DisplayRole] = "edge";
    m_roles[SourceRole] = "source";
    m_roles[SourceXRole] = "sourceX";
    m_roles[SourceYRole] = "sourceY";
    m_roles[TargetRole] = "target";
    m_roles[TargetXRole] = "targetX";
    m_roles[TargetYRole] = "targetY";
    m_roles[BendsRole] = "bends";
}

int EdgeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return count();
}

QHash<int, QByteArray> EdgeModel::roleNames() const
{
    return m_roles;
}

QVariant EdgeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    ogdf::edge e = m_edges[index.row()];
    switch (role) {
    case Qt::DisplayRole:
        return QVariant(m_graph->edge(e));
    case SourceRole:
        return QVariant(m_graph->node(e->source()));
    case SourceXRole:
        return QVariant(m_graph->attributes().x(e->source()));
    case SourceYRole:
        return QVariant(m_graph->attributes().y(e->source()));
    case TargetRole:
        return QVariant(m_graph->node(e->target()));
    case TargetXRole:
        return QVariant(m_graph->attributes().x(e->target()));
    case TargetYRole:
        return QVariant(m_graph->attributes().y(e->target()));
    case BendsRole: {
        QVariantList points;
        ogdf::DPolyline &bends = m_graph->attributes().bends(e);
        if (bends.size() == 0) {
            m_graph->attributes().addNodeCenter2Bends();
        }
        ogdf::DPolyline::const_iterator bend;
        for (bend = bends.begin(); bend != bends.end(); bend++) {
            points.append(QPointF((*bend).m_x, (*bend).m_y));
        }
        return points;
    }
    default:
        return QVariant();
    }
}

void EdgeModel::reInit()
{
    beginResetModel();
    ogdf::edge e;
    forall_edges (e, m_graph->g()) {
        m_edges.append(e);
        m_graph->insertEdge(e, QString("%1").arg(e->index()));
    }
    endResetModel();
    emit countChanged();
}

void EdgeModel::cleared()
{
    beginResetModel();
    m_edges.clear();
    m_graph->clearEdges();
    endResetModel();
    emit countChanged();
}

void EdgeModel::nodeAdded(ogdf::node v)
{
}

void EdgeModel::nodeDeleted(ogdf::node v)
{
}

void EdgeModel::edgeAdded(ogdf::edge e)
{
    beginInsertRows(QModelIndex(), m_edges.count(), m_edges.count());
    m_edges.append(e);
    m_graph->insertEdge(e, QString("%1").arg(e->index()));
    endInsertRows();
    emit countChanged();
}

void EdgeModel::edgeDeleted(ogdf::edge e)
{
    int index = m_edges.indexOf(e);
    Q_ASSERT(index != -1);
    beginRemoveRows(QModelIndex(), index, index);
    m_edges.removeAt(index);
    m_graph->removeEdge(e);
    endRemoveRows();
    emit countChanged();
}

void EdgeModel::attributesChanged()
{
    QModelIndex top = createIndex(0, 0);
    QModelIndex bottom = createIndex(count(), 0);
    QVector<int> roles;
    roles << SourceRole << SourceXRole << SourceYRole
          << TargetRole <<  TargetXRole << TargetYRole
          << BendsRole;
    emit dataChanged(top, bottom, roles);
}

int EdgeModel::count() const
{
    return m_edges.count();
}

QString EdgeModel::get(int index) const
{
    ogdf::edge e = m_edges.value(index);
    if (e) {
        return m_graph->edge(e);
    } else {
        return QString();
    }
}

QString EdgeModel::getSource(int index) const
{
    ogdf::edge e = m_edges.value(index);
    if (e) {
        return m_graph->node(e->source());
    } else {
        return QString();
    }
}

QString EdgeModel::getTarget(int index) const
{
    ogdf::edge e = m_edges.value(index);
    if (e) {
        return m_graph->node(e->target());
    } else {
        return QString();
    }
}

void EdgeModel::insert(const QString &edge, const QString &source, const QString &target)
{
    ogdf::node v = m_graph->v(source);
    ogdf::node w = m_graph->v(target);
    if (!v) {
        qmlInfo(this) << "Source node \"" << source << "\" does not exist";
    } else if (!w) {
        qmlInfo(this) << "Target node \"" << target << "\" does not exist";
    } else {
        ogdf::edge e = m_graph->g().newEdge(v, w);
        m_graph->insertEdge(e, edge);
        m_graph->layout()->invalidate();
    }
}

void EdgeModel::remove(const QString &edge)
{
    ogdf::edge e = m_graph->e(edge);
    if (e) {
        m_graph->g().delEdge(e);
        m_graph->layout()->invalidate();
    }
}
