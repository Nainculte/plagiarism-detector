#ifndef DETECTIONMODULEINTERFACE_H
#define DETECTIONMODULEINTERFACE_H

#include <QString>
#include <QObject>
#include <QVariant>
#include "DetectionModuleHolder.h"

class QDialog;

class DetectionModuleInterface
{
public:
    virtual ~DetectionModuleInterface(void) {}

    virtual QString getModuleInformation(void) = 0;
    virtual QDialog &getParameterForm(void) = 0;
    virtual bool startAnalysis(void) = 0;
    virtual bool stopAnalysis(void) = 0;
    virtual bool pauseAnalysis(void) = 0;
    virtual void setSources(QList<QHash<QString, QVariant> >) = 0;
    virtual QList<QHash<QString, QVariant> > getAnalysisResults(void) = 0;
    virtual void setDelegate(DetectionModuleHolder *delegate) = 0;

    static const int started = 0;
    static const int resumed = 1;
    static const int paused = 2;
    static const int stopped  = 3;
    static const int finished = 4;
};

#define DetectionModuleInterface_iid "DetectionModuleInterface_iid"
Q_DECLARE_INTERFACE(DetectionModuleInterface, DetectionModuleInterface_iid)

#endif // DETECTIONMODULEINTERFACE_H
