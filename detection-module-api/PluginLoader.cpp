#include <QPluginLoader>
#include <QObject>
#include <iostream>
#include "PluginLoader.h"

PluginLoader::PluginLoader()
{
    plugin = NULL;
}

PluginLoader::~PluginLoader()
{
    if (plugin)
        delete plugin;
}

void PluginLoader::loadPlugin(const QString &name)
{
    QPluginLoader loader(name);
    QObject *plug = loader.instance();
    if (plug)
    {
        plugin = qobject_cast<DetectionModuleInterface *>(plug);
        if (plugin)
            std::cout << "all good" << std::endl << plugin->getModuleInformation().toStdString() << std::endl;
        else
            std::cout << "not a dmodule" << std::endl;
    }
    else
        std::cout << "no plugin of this name" << std::endl;
}
