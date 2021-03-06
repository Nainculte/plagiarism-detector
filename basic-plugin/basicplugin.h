#ifndef BASICPLUGIN_H
#define BASICPLUGIN_H

#include <QFile>
#include "basic-plugin_global.h"
#include "../Plagiarism-Detector/DetectionModuleInterface.h"
#include <QDialog>

class BASICPLUGINSHARED_EXPORT Basicplugin : public QObject, DetectionModuleInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "basicplugin")
    Q_INTERFACES(DetectionModuleInterface)

public:
    Basicplugin();
    virtual ~Basicplugin(void);

    virtual QString getModuleInformation(void);
    virtual QDialog &getParameterForm(void);
    virtual bool startAnalysis(void);
    virtual bool stopAnalysis(void);
    virtual bool pauseAnalysis(void);
    virtual void setSources(QList<QHash<QString, QVariant> > list);
    virtual QList<AnalysisResult *> getAnalysisResults(void);
    virtual void setDelegate(DetectionModuleHolder *delegate);

private:
    float compareFiles(QFile &ori, QFile &o);

private:
    DetectionModuleHolder *delegate;
    QList<QHash<QString, QVariant> > sources;
    QDialog *parameterForm;
    QList<AnalysisResult *> results;
};

class ParameterDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ParameterDialog(QWidget *parent = 0);
};

#endif // BASICPLUGIN_H
