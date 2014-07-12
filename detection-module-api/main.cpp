#include <QCoreApplication>
#include "PluginLoader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    PluginLoader pl;

    pl.loadPlugin("C:\\cygwin64\\home\\jacqui_a\\plagiarism-detector\\build-basic-plugin-Desktop_Qt_5_3_MinGW_32bit-Debug\\debug\\basic-plugin.dll");
    return a.exec();
}
