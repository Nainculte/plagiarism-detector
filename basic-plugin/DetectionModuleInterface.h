#ifndef DETECTIONMODULEINTERFACE_H
#define DETECTIONMODULEINTERFACE_H

#include <QString>
#include <QObject>

class DetectionModuleInterface
{
public:
    virtual ~DetectionModuleInterface(void) {}

    virtual QString GetModuleInformation(void) = 0;
    virtual bool StartAnalysis(void) = 0;
};

#define DetectionModuleInterface_iid "DetectionModuleInterface_iid"
Q_DECLARE_INTERFACE(DetectionModuleInterface, DetectionModuleInterface_iid)

#endif // DETECTIONMODULEINTERFACE_H
