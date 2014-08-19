#ifndef BASICPLUGIN_H
#define BASICPLUGIN_H

#include <QObject>
#include <QWidget>
#include <QString>
#include "basic-plugin_global.h"
#include "DetectionModuleInterface.h"
#include "DetectionModuleHolder.h"

class BASICPLUGINSHARED_EXPORT Basicplugin : public QObject, DetectionModuleInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "basicplugin")
    Q_INTERFACES(DetectionModuleInterface)

public:
    Basicplugin();
    virtual ~Basicplugin(void);

    virtual QString getModuleInformation(void);
    virtual QDialog getParameterForm(void);
    virtual bool startAnalysis(void);
    virtual bool stopAnalysis(void);
    virtual bool pauseAnalysis(void);
    virtual void setSources(QList<QString> list);
    virtual QList<QHash<QString, QVariant> > getAnalysisResults(void);
    virtual bool setCallback(QString id, void (DetectionModuleHolder::*delegate)(void));
    virtual void setDelegate(DetectionModuleHolder *delegate);

private:
    DetectionModuleHolder *delegate;
    QList<QString> sources;

};

#endif // BASICPLUGIN_H
