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
#ifndef NODEMODEL_H
#define NODEMODEL_H

#include <QAbstractListModel>
#include "ogdf/basic/GraphAttributes.h"
#include "ogdf/basic/GraphObserver.h"

/**
 *
 */
class NodeModel : public QAbstractListModel, public ogdf::GraphObserver
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    //model API
    enum Roles {
        XRole = Qt::UserRole + 1,
        YRole,
        WidthRole,
        HeightRole
    };

    NodeModel(ogdf::GraphAttributes *attributes, QObject *parent = 0);
    ~NodeModel();

    ogdf::node node(int index);
    void attributesChanged();

    // QAbstractListModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    // GraphObserver
    void reInit();
    void cleared();
    void nodeAdded(ogdf::node v);
    void nodeDeleted(ogdf::node v);
    void edgeAdded(ogdf::edge e);
    void edgeDeleted(ogdf::edge e);

    // QML API
    int count() const;

signals:
    void countChanged();

private:
    Q_DISABLE_COPY(NodeModel)

    ogdf::GraphAttributes *m_attributes;
    QHash<int, QByteArray> m_roles;
    QList<ogdf::node> m_nodes;
};

#endif
