#ifndef SUMMARYMODULE_H
#define SUMMARYMODULE_H

#include "DetectionModuleInterface.h"
#include <QDialog>

class SummaryModule : public DetectionModuleInterface
{
public:
    SummaryModule();
    virtual ~SummaryModule();

    virtual QString getModuleInformation(void);
    virtual QDialog &getParameterForm(void);
    virtual bool startAnalysis(void);
    virtual bool stopAnalysis(void);
    virtual bool pauseAnalysis(void);
    virtual void setSources(QList<QHash<QString, QVariant> >);
    virtual QList<AnalysisResult *> getAnalysisResults(void);
    virtual void setDelegate(DetectionModuleHolder *delegate);

    void summarize(QList<QList<AnalysisResult *> >lists);

private:
    QList<AnalysisResult *> list;
    DetectionModuleHolder *delegate;
};

class SummaryDialog : public QDialog
{
public:
    SummaryDialog(QWidget *parent = 0);
    ~SummaryDialog();
};

#endif // SUMMARYMODULE_H
