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
#include "ogdfplugin.h"
#include "nodemodel.h"
#include "edgemodel.h"
#include "graphlayout.h"
#include "graph.h"
#include <QtQml>

void OGDFPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("OGDF"));
    qmlRegisterUncreatableType<NodeModel>(uri, 1, 0, "NodeModel", QString());
    qmlRegisterUncreatableType<EdgeModel>(uri, 1, 0, "EdgeModel", QString());
    qmlRegisterUncreatableType<GraphLayout>(uri, 1, 0, "GraphLayout", QString());
    qmlRegisterType<Graph>(uri, 1, 0, "Graph");
}
