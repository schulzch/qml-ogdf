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
import QtQuick 2.0
import OGDF 1.0

Item {
    property QtObject model: null
    property Component nodeDelegate: Text { text: model.node }
    property Component edgeDelegate: EdgeSpline {}
    id: root
    x: childrenRect.x
    y: childrenRect.y
    width: childrenRect.width
    height: childrenRect.height
    Repeater {
        model: root.model === null ? null : root.model.edges
        delegate: Item {
            readonly property var itemModel: model
            id: edgeItem
            x: 0
            y: 0
            width: childrenRect.width
            height: childrenRect.height
            Loader {
                property var model: edgeItem.itemModel
                sourceComponent: root.edgeDelegate
                Component.onDestruction: {
                    // XXX: Workaround Components, that get destroyed after the Loader.
                    model = { edge: "",
                        source: "", sourceX: 0, sourceY: 0,
                        target: "", targetX: 0, targetY: 0,
                        bends: [] };
                }
            }
        }
    }
    Repeater {
        model: root.model === null ? null : root.model.nodes
        delegate: Item {
            readonly property var itemModel: model
            id: nodeItem
            x: model.x - model.width / 2
            y: model.y - model.height / 2
            width: childrenRect.width
            height: childrenRect.height
            Binding {
                target: model
                property: "width"
                value: nodeItem.width
            }
            Binding {
                target: model
                property: "height"
                value: nodeItem.height
            }
            Loader {
                property var model: nodeItem.itemModel
                sourceComponent: root.nodeDelegate
                Component.onDestruction: {
                    // XXX: Workaround Components, that get destroyed after the Loader.
                    model = { node: "", x: 0, y: 0, width: 0, height: 0 };
                }
            }
        }
    }
}
