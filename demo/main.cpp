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
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQuickView>
#include <QScreen>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc,argv);
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    QQuickView view;
    view.connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    view.setTitle("OGDF Demo");
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/qml/main.qml"));
    view.setPosition(screenGeometry.x() + (screenGeometry.width() - view.width()) / 2,
                     screenGeometry.y() + (screenGeometry.height() - view.height()) / 2);
    view.show();
    return app.exec();
}
