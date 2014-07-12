#ifndef DETECTIONMODULEINTERFACE_H
#define DETECTIONMODULEINTERFACE_H

#include <QString>
#include <QObject>
#include "DetectionModuleHolder.h"

class DetectionModuleInterface
{
public:
    virtual ~DetectionModuleInterface(void) {}

    virtual QString getModuleInformation(void) = 0;
    virtual QString getParameterForm(void) = 0;
    virtual bool startAnalysis(void) = 0;
    virtual bool stopAnalysis(void) = 0;
    virtual bool pauseAnalysis(void) = 0;
    virtual bool setSources(void) = 0;
    virtual QString getAnalysisResults(void) = 0;
    virtual bool setCallback(QString id, void (DetectionModuleHolder::*delegate)(void)) = 0;
};

#define DetectionModuleInterface_iid "DetectionModuleInterface_iid"
Q_DECLARE_INTERFACE(DetectionModuleInterface, DetectionModuleInterface_iid)

#endif // DETECTIONMODULEINTERFACE_H
