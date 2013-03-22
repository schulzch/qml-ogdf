#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include "nodemodel.h"
#include "edgemodel.h"
#include "ogdf/basic/Graph.h"
#include "ogdf/basic/GraphAttributes.h"

/**
 * @brief The Graph class
 */
class Graph : public QObject
{
    Q_OBJECT
    Q_PROPERTY(NodeModel *nodes READ nodes CONSTANT)
    Q_PROPERTY(EdgeModel *edges READ edges CONSTANT)
public:
    Graph(QObject *parent = 0);
    ~Graph();

    NodeModel *nodes();
    EdgeModel *edges();

    Q_INVOKABLE void randomSimpleGraph(int nodeCount, int edgeCount);

    Q_INVOKABLE int addNode(double x, double y, double width, double height);
    Q_INVOKABLE void removeNode(int index);

    Q_INVOKABLE int addEdge(int sourceNode, int targetNode);
    Q_INVOKABLE void removeEdge(int index);

    Q_INVOKABLE void clear();

    Q_INVOKABLE void fmmmLayout();

private:
    Q_DISABLE_COPY(Graph)

    ogdf::Graph m_graph;
    ogdf::GraphAttributes m_attributes;
    NodeModel m_nodes;
    EdgeModel m_edges;
};

#endif
