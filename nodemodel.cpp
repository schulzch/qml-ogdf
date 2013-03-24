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

NodeModel::NodeModel(ogdf::GraphAttributes *attributes, QObject *parent)
    : QAbstractListModel(parent), ogdf::GraphObserver(&attributes->constGraph()),
      m_attributes(attributes)
{
    m_roles[Qt::DisplayRole] = "index";
    m_roles[XRole] = "x";
    m_roles[YRole] = "y";
    m_roles[WidthRole] = "width";
    m_roles[HeightRole] = "height";
}

NodeModel::~NodeModel()
{
}

void NodeModel::attributesChanged()
{
    QModelIndex top = createIndex(0, 0);
    QModelIndex bottom = createIndex(count(), 0);
    emit dataChanged(top, bottom);
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

QVariant NodeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    ogdf::node v = m_nodes[index.row()];
    switch (role) {
    case Qt::DisplayRole:
        return QVariant(v->index());
    case XRole:
        return QVariant(m_attributes->x(v));
    case YRole:
        return QVariant(m_attributes->y(v));
    case WidthRole:
        return QVariant(m_attributes->width(v));
    case HeightRole:
        return QVariant(m_attributes->height(v));
    default:
        return QVariant();
    }
}

void NodeModel::reInit()
{
    beginResetModel();
    ogdf::node v;
    forall_nodes (v, m_attributes->constGraph()) {
        m_nodes.append(v);
    }
    endResetModel();
    emit countChanged();
}

void NodeModel::cleared()
{
    beginResetModel();
    m_nodes.clear();
    endResetModel();
    emit countChanged();
}

void NodeModel::nodeAdded(ogdf::node v)
{
    beginInsertRows(QModelIndex(), m_nodes.count(), m_nodes.count());
    m_nodes.append(v);
    endInsertRows();
    emit countChanged();
}

void NodeModel::nodeDeleted(ogdf::node v)
{
    int index = m_nodes.indexOf(v);
    Q_ASSERT(index != -1);
    beginRemoveRows(QModelIndex(), index, index);
    m_nodes.removeAt(index);
    endRemoveRows();
    emit countChanged();
}

void NodeModel::edgeAdded(ogdf::edge e)
{
}

void NodeModel::edgeDeleted(ogdf::edge e)
{
}

int NodeModel::count() const
{
    return m_nodes.count();
}
