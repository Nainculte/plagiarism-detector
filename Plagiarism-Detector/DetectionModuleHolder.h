#ifndef DETECTIONMODULEHOLDER_H
#define DETECTIONMODULEHOLDER_H

#include <QString>

class DetectionModuleInterface;

class DetectionModuleHolder
{
private:
    DetectionModuleInterface *plugin_;
    QString pluginInfo_;
    QString parameterForm_;

public:
    DetectionModuleHolder(DetectionModuleInterface *plugin);
    ~DetectionModuleHolder();

public:
    void setStatusCallback(int status);
    void setProgressCallback(int progress);
};

#include "DetectionModuleInterface.h"

#endif // DETECTIONMODULEHOLDER_H
