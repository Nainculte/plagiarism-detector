#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Plagiarism-Detector");
    MainWindow w;
    w.setWindowTitle("Plagiarism-Detector");
    w.show();

    return a.exec();
}
