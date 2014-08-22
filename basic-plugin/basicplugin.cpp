#include "basicplugin.h"


Basicplugin::Basicplugin()
{
    delegate = Q_NULLPTR;
    parameterForm = new ParameterDialog();
}

Basicplugin::~Basicplugin(void)
{

}

QString Basicplugin::getModuleInformation()
{
    return QString("Test Detection Module");
}

QDialog& Basicplugin::getParameterForm()
{
    return *parameterForm;
}

bool Basicplugin::startAnalysis()
{
    if (delegate)
    {
        delegate->statusChanged(DetectionModuleInterface::started);

        //to remove here for testing purpose
        delegate->statusChanged(DetectionModuleInterface::finished);
    }
    return true;
}

bool Basicplugin::stopAnalysis()
{
    if (delegate)
    {
        delegate->statusChanged(DetectionModuleInterface::stopped);
    }
    return true;
}

bool Basicplugin::pauseAnalysis()
{
    if (delegate)
    {
        delegate->statusChanged(DetectionModuleInterface::paused);
    }
    return true;
}

void Basicplugin::setSources(QList<QHash<QString, QVariant> > list)
{
    sources = list;
}

QList<AnalysisResult *> Basicplugin::getAnalysisResults()
{
    results.clear();
    for (int i = 0; i < sources.count(); ++i)
    {
        for (int j = i + 1; j < sources.count(); ++j)
        {
            AnalysisResult *res = new AnalysisResult((i+1)*(j+1), QString::number(i), QString::number(j), QHash<QString, QVariant>());
            results << res;
        }
    }

    return results;
}


void Basicplugin::setDelegate(DetectionModuleHolder *delegate)
{
    this->delegate = delegate;
}

ParameterDialog::ParameterDialog(QWidget *parent) : QDialog(parent)
{

}
