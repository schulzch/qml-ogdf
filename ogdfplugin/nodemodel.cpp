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
#include "nodemodel.h"
#include "graph.h"

NodeModel::NodeModel(Graph *graph)
    : QAbstractListModel(graph), ogdf::GraphObserver(&graph->g()),
      m_graph(graph)
{
    m_roles[Qt::DisplayRole] = "node";
    m_roles[XRole] = "x";
    m_roles[YRole] = "y";
    m_roles[WidthRole] = "width";
    m_roles[HeightRole] = "height";
}

int NodeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return count();
}

QHash<int, QByteArray> NodeModel::roleNames() const
{
    return m_roles;
}

Qt::ItemFlags NodeModel::flags(const QModelIndex &index) const
{
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

QVariant NodeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    ogdf::node v = m_nodes[index.row()];
    switch (role) {
    case Qt::DisplayRole:
        return QVariant(m_graph->node(v));
    case XRole:
        return QVariant(m_graph->attributes().x(v));
    case YRole:
        return QVariant(m_graph->attributes().y(v));
    case WidthRole:
        return QVariant(m_graph->attributes().width(v));
    case HeightRole:
        return QVariant(m_graph->attributes().height(v));
    default:
        return QVariant();
    }
}

bool NodeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }
    ogdf::node v = m_nodes[index.row()];
    switch (role) {
    case XRole:
        m_graph->attributes().x(v) = value.toDouble();
        break;
    case YRole:
        m_graph->attributes().y(v) = value.toDouble();
        break;
    case WidthRole:
        m_graph->attributes().width(v) = value.toDouble();
        break;
    case HeightRole:
        m_graph->attributes().height(v) = value.toDouble();
        break;
    default:
        return false;
    }
    QVector<int> roles;
    roles << XRole << YRole << WidthRole << HeightRole;
    emit dataChanged(index, index, roles);
    m_graph->layout()->invalidate();
    return true;
}

void NodeModel::reInit()
{
    beginResetModel();
    ogdf::node v;
    forall_nodes (v, m_graph->g()) {
        m_nodes.append(v);
        m_graph->insertNode(v, QString("%1").arg(v->index()));
    }
    endResetModel();
    emit countChanged();
}

void NodeModel::cleared()
{
    beginResetModel();
    m_nodes.clear();
    m_graph->clearNodes();
    endResetModel();
    emit countChanged();
}

void NodeModel::nodeAdded(ogdf::node v)
{
    beginInsertRows(QModelIndex(), m_nodes.count(), m_nodes.count());
    m_nodes.append(v);
    m_graph->insertNode(v, QString("%1").arg(v->index()));
    endInsertRows();
    emit countChanged();
}

void NodeModel::nodeDeleted(ogdf::node v)
{
    int index = m_nodes.indexOf(v);
    Q_ASSERT(index != -1);
    beginRemoveRows(QModelIndex(), index, index);
    m_nodes.removeAt(index);
    m_graph->removeNode(v);
    endRemoveRows();
    emit countChanged();
}

void NodeModel::edgeAdded(ogdf::edge e)
{
}

void NodeModel::edgeDeleted(ogdf::edge e)
{
}

void NodeModel::attributesChanged()
{
    QModelIndex top = createIndex(0, 0);
    QModelIndex bottom = createIndex(count(), 0);
    QVector<int> roles;
    roles << XRole << YRole << WidthRole << HeightRole;
    emit dataChanged(top, bottom, roles);
}

int NodeModel::count() const
{
    return m_nodes.count();
}

QString NodeModel::get(int index) const
{
    ogdf::node v = m_nodes.value(index);
    if (v) {
        return m_graph->node(v);
    } else {
        return QString();
    }
}

void NodeModel::insert(const QString &node)
{
    ogdf::node v = m_graph->g().newNode();
    m_graph->insertNode(v, node);
    m_graph->layout()->invalidate();
}

void NodeModel::remove(const QString &node)
{
    ogdf::node v = m_graph->v(node);
    if (v) {
        m_graph->g().delNode(v);
        m_graph->layout()->invalidate();
    }
}
