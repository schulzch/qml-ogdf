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
#ifndef EDGEMODEL_H
#define EDGEMODEL_H

#include <QAbstractListModel>
#include "ogdf/basic/GraphAttributes.h"
#include "ogdf/basic/GraphObserver.h"

class Graph;

/**
 * This class provides a list model for edges.
 */
class EdgeModel : public QAbstractListModel, public ogdf::GraphObserver
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum Roles {
        SourceRole = Qt::UserRole + 1,
        SourceXRole,
        SourceYRole,
        TargetRole,
        TargetXRole,
        TargetYRole,
        BendsRole
    };

    EdgeModel(Graph *graph);

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

    // C++ API
    void attributesChanged();

    // QML API
    int count() const;
    Q_INVOKABLE QString get(int index) const;
    Q_INVOKABLE QString getSource(int index) const;
    Q_INVOKABLE QString getTarget(int index) const;
    Q_INVOKABLE void insert(const QString &edge, const QString &source, const QString &target);
    Q_INVOKABLE void remove(const QString &edge);

signals:
    void countChanged();

private:
    Q_DISABLE_COPY(EdgeModel)

    Graph *m_graph;
    QHash<int, QByteArray> m_roles;
    QList<ogdf::edge> m_edges;
};

#endif
