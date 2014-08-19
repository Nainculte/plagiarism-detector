#include "basicplugin.h"


Basicplugin::Basicplugin()
{
    delegate = Q_NULLPTR;
}

Basicplugin::~Basicplugin(void)
{

}

QString Basicplugin::getModuleInformation()
{
    return QString("Test Detection Module");
}

QDialog Basicplugin::getParameterForm()
{
    return QDialog();
}

bool Basicplugin::StartAnalysis()
{
    if (delegate)
    {
        delegate->statusChanged(DetectionModuleInterface::started);
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

void Basicplugin::setSources(QList<QString> list)
{
    sources = list;
}

QList<QHash<QString, QVariant> > Basicplugin::getAnalysisResults()
{
    return *QList();
}

bool Basicplugin::setCallback(QString id, void (DetectionModuleHolder::*delegate)())
{
    Q_UNUSED(delegate);
    return true;
}


void Basicplugin::setDelegate(DetectionModuleHolder *delegate)
{
    this->delegate = delegate;
}
