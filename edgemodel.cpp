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

EdgeModel::EdgeModel(ogdf::GraphAttributes *attributes, QObject *parent)
    : QAbstractListModel(parent), ogdf::GraphObserver(&attributes->constGraph()),
      m_attributes(attributes)
{
    m_roles[Qt::DisplayRole] = "index";
    m_roles[SourceX] = "sourceX";
    m_roles[SourceY] = "sourceY";
    m_roles[TargetX] = "targetX";
    m_roles[TargetY] = "targetY";
    m_roles[BendsRole] = "bends";
}

EdgeModel::~EdgeModel()
{
}

void EdgeModel::attributesChanged()
{
    QModelIndex top = createIndex(0, 0);
    QModelIndex bottom = createIndex(count(), 0);
    emit dataChanged(top, bottom);
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
        return QVariant(e->index());
    case SourceX:
        return QVariant(m_attributes->x(e->source()));
    case SourceY:
        return QVariant(m_attributes->y(e->source()));
    case TargetX:
        return QVariant(m_attributes->x(e->target()));
    case TargetY:
        return QVariant(m_attributes->y(e->target()));
    case BendsRole: {
        QVariantList points;
        ogdf::DPolyline &bends = m_attributes->bends(e);
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
    forall_edges (e, m_attributes->constGraph()) {
        m_edges.append(e);
    }
    endResetModel();
    emit countChanged();
}

void EdgeModel::cleared()
{
    beginResetModel();
    m_edges.clear();
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
    endInsertRows();
    emit countChanged();
}

void EdgeModel::edgeDeleted(ogdf::edge e)
{
    int index = m_edges.indexOf(e);
    Q_ASSERT(index != -1);
    beginRemoveRows(QModelIndex(), index, index);
    m_edges.removeAt(index);
    endRemoveRows();
    emit countChanged();
}

int EdgeModel::count() const
{
    return m_edges.count();
}
