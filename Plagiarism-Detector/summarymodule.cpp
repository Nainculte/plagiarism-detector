#include "summarymodule.h"
#include <QList>
#include <QHash>
#include <QString>
#include <QVariant>

SummaryModule::SummaryModule()
{
}

SummaryModule::~SummaryModule()
{
}

QString SummaryModule::getModuleInformation()
{
    return "Summary";
}

QDialog &SummaryModule::getParameterForm()
{
    return *(new SummaryDialog());
}

bool SummaryModule::startAnalysis()
{
    if (delegate)
        delegate->statusChanged(DetectionModuleInterface::finished);
    return true;
}

bool SummaryModule::stopAnalysis()
{
    if (delegate)
        delegate->statusChanged(DetectionModuleInterface::stopped);
    return true;
}

bool SummaryModule::pauseAnalysis()
{
    if (delegate)
        delegate->statusChanged(DetectionModuleInterface::paused);
    return true;
}

void SummaryModule::setSources(QList<QHash<QString, QVariant> >)
{
}

QList<AnalysisResult *> SummaryModule::getAnalysisResults()
{
    return list;
}

void SummaryModule::setDelegate(DetectionModuleHolder *delegate)
{
    this->delegate = delegate;
}

void SummaryModule::summarize(QList<QList<AnalysisResult *> >lists)
{

    while (list.count() != lists.first().count())
    {
        float avg = 0.0;
        QString id1, id2;
        foreach (QList<AnalysisResult *>list, lists)
        {
            avg += list.at(this->list.count())->similarity();
        }
        avg /= lists.count();
        id1 = lists.first().at(list.count())->id1();
        id1 = lists.first().at(list.count())->id2();
        AnalysisResult *average = new AnalysisResult(avg, id1, id2, QHash<QString, QVariant>());
        list << average;
    }
}


SummaryDialog::SummaryDialog(QWidget *parent)
    : QDialog(parent)
{
}

SummaryDialog::~SummaryDialog()
{
}
