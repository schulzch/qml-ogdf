#ifndef OGDFPLUGIN_H
#define OGDFPLUGIN_H

#include <QQmlExtensionPlugin>

class OGDFPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
public:
    void registerTypes(const char *uri);
};

#endif
