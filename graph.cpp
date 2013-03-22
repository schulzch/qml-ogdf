#include "graph.h"
#include "ogdf/basic/graph_generators.h"
#include "ogdf/energybased/FMMMLayout.h"
#include <QDebug>

Graph::Graph(QObject *parent)
    : QObject(parent), m_graph(),
      m_attributes(m_graph, ogdf::GraphAttributes::nodeGraphics |
                   ogdf::GraphAttributes::edgeGraphics),
      m_nodes(&m_attributes), m_edges(&m_attributes)
{
    // Do nothing.
}

Graph::~Graph()
{
}

NodeModel *Graph::nodes()
{
    return &m_nodes;
}

EdgeModel *Graph::edges()
{
    return &m_edges;
}

void Graph::randomSimpleGraph(int nodeCount, int edgeCount)
{
    ogdf::randomSimpleGraph(m_graph, nodeCount, edgeCount);
}

int Graph::addNode(double x, double y, double width, double height)
{
    ogdf::node v = m_graph.newNode();
    m_attributes.x(v) = x;
    m_attributes.y(v) = y;
    m_attributes.width(v) = width;
    m_attributes.height(v) = height;
    m_attributes.shapeNode(v) = ogdf::GraphAttributes::rectangle;
    return v->index();
}

void Graph::removeNode(int index)
{
    bool found = false;
    ogdf::node v;
    forall_nodes (v, m_graph) {
        if (v->index() == index) {
            m_graph.delNode(v);
            found = true;
            break;
        }
    }
    if (!found) {
        qWarning() << "Can not remove node with index" << index;
    }
}

int Graph::addEdge(int sourceNode, int targetNode)
{
    bool found1 = false;
    ogdf::node v1;
    forall_nodes (v1, m_graph) {
        if (v1->index() == sourceNode) {
            found1 = true;
            break;
        }
    }
    bool found2 = false;
    ogdf::node v2;
    forall_nodes (v2, m_graph) {
        if (v2->index() == targetNode) {
            found2 = true;
            break;
        }
    }
    if (found1 && found2) {
        ogdf::edge e = m_graph.newEdge(v1, v2);
        //ogdf::DPolyline &p = m_attributes.bends(e);
        //p.pushBack(ogdf::DPoint(10,20*e->index()));
        //p.pushBack(ogdf::DPoint(20*e->index(),10));
        return e->index();
    } else {
        return -1;
    }

}

void Graph::removeEdge(int index)
{
    bool found = false;
    ogdf::edge e;
    forall_edges (e, m_graph) {
        if (e->index() == index) {
            m_graph.delEdge(e);
            found = true;
            break;
        }
    }
    if (!found) {
        qWarning() << "Can not remove egde with index" << index;
    }
}

void Graph::clear()
{
    m_graph.clear();
}

void Graph::fmmmLayout()
{
    ogdf::FMMMLayout fmmm;
    fmmm.useHighLevelOptions(true);
    fmmm.unitEdgeLength(15.0);
    fmmm.newInitialPlacement(true);
    fmmm.qualityVersusSpeed(ogdf::FMMMLayout::qvsGorgeousAndEfficient);
    fmmm.call(m_attributes);
    m_nodes.attributesChanged();
    m_edges.attributesChanged();
}
