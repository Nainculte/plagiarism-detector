#include "basicplugin.h"


Basicplugin::Basicplugin()
{
}

Basicplugin::~Basicplugin(void)
{

}

QString Basicplugin::GetModuleInformation()
{
    return QString("test");
}

bool Basicplugin::StartAnalysis()
{
    return true;
}
