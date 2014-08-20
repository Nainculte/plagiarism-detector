#ifndef MODULERESULTWRAPPER_H
#define MODULERESULTWRAPPER_H

#include "DetectionModuleInterface.h"
#include <QList>
#include <QHash>
#include <QVariant>

class ModuleResultWrapper
{
public:
    ModuleResultWrapper(DetectionModuleInterface *module,
                        const QList<AnalysisResult *> &results);
    ~ModuleResultWrapper();

    DetectionModuleInterface *module();
    QList<AnalysisResult *> results();

private:
    DetectionModuleInterface *_module;
    QList<AnalysisResult *> _results;
};

#endif // MODULERESULTWRAPPER_H
