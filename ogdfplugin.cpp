#include "ogdfplugin.h"
#include "nodemodel.h"
#include "edgemodel.h"
#include "graph.h"
#include <QtQml>

void OGDFPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("OGDF"));
    qmlRegisterType<Graph>(uri, 1, 0, "Graph");
    qmlRegisterUncreatableType<NodeModel>(uri, 1, 0, "NodeModel", QString());
    qmlRegisterUncreatableType<EdgeModel>(uri, 1, 0, "EdgeModel", QString());
}
