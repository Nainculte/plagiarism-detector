#include "moduleresultwrapper.h"

ModuleResultWrapper::ModuleResultWrapper(DetectionModuleInterface *module,
                                         const QList<AnalysisResult *> &results)
    : _module(module), _results(results)
{
}

ModuleResultWrapper::~ModuleResultWrapper()
{
}

DetectionModuleInterface *ModuleResultWrapper::module()
{
    return _module;
}

QList<AnalysisResult *> ModuleResultWrapper::results()
{
    return _results;
}
