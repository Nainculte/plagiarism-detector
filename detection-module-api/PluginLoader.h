#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "DetectionModuleInterface.h"

class PluginLoader
{
private:
    DetectionModuleInterface *plugin;

public:
    PluginLoader();
    ~PluginLoader(void);

    void loadPlugin(const QString &name);
};

#endif // PLUGINLOADER_H
