#ifndef EDGEMODEL_H
#define EDGEMODEL_H

#include <QAbstractListModel>
#include "ogdf/basic/GraphAttributes.h"
#include "ogdf/basic/GraphObserver.h"

/**
 * @brief The Node class
 */
class EdgeModel : public QAbstractListModel, public ogdf::GraphObserver
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    //model API
    enum Roles {
        SourceX = Qt::UserRole + 1,
        SourceY,
        TargetX,
        TargetY,
        BendsRole
    };

    EdgeModel(ogdf::GraphAttributes *attributes, QObject *parent = 0);
    ~EdgeModel();

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
    Q_DISABLE_COPY(EdgeModel)

    QHash<int, QByteArray> m_roles;
    ogdf::GraphAttributes *m_attributes;
    QList<ogdf::edge> m_edges;
};

#endif
