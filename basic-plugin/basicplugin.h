#ifndef BASICPLUGIN_H
#define BASICPLUGIN_H

#include <QObject>
#include "basic-plugin_global.h"
#include "DetectionModuleInterface.h"

class BASICPLUGINSHARED_EXPORT Basicplugin : public QObject, DetectionModuleInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "basicplugin")
    Q_INTERFACES(DetectionModuleInterface)

public:
    Basicplugin();
    virtual ~Basicplugin(void);

    virtual QString GetModuleInformation();
    virtual bool StartAnalysis();
};

#endif // BASICPLUGIN_H
