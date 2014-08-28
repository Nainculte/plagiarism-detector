#include <QFile>
#include <QTextStream>
#include "basicplugin.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

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
        if (sources.size() == 0)
            return false;
        delegate->statusChanged(DetectionModuleInterface::started);
        QListIterator<QHash<QString, QVariant> > it(sources);
        while (it.hasNext())
        {
            if (it.peekNext()["checked"] == true && it.peekNext()["file"] == true)
            {
                QFile origin(it.peekNext()["fileName"].toString());
                QListIterator<QHash<QString, QVariant> > fromOrigin(it);

                if (fromOrigin.hasNext())
                    fromOrigin.next();
                while (fromOrigin.hasNext())
                {
                    if (fromOrigin.peekNext()["checked"] == true && fromOrigin.peekNext()["file"] == true)
                    {
                        float res = 0;
                        QFile compared(fromOrigin.peekNext()["fileName"].toString());
                        if (origin.open(QIODevice::ReadOnly))
                        {
                            if (compared.open(QIODevice::ReadOnly))
                            {
                                res = this->compareFiles(origin, compared);
                                compared.close();
                            }
                            origin.close();
                        }
                        results.push_back(new AnalysisResult(res, it.peekNext()["fileName"].toString(),
                                            fromOrigin.peekNext()["filenNme"].toString(), QHash<QString, QVariant >()));
                    }
                    fromOrigin.next();
                }
            }
            it.next();
        }
        //to remove here for testing purpose
        delegate->statusChanged(DetectionModuleInterface::finished);
    }
    return true;
}

float Basicplugin::compareFiles(QFile &ori, QFile &o)
{
    QTextStream oriIn(&ori);
    QTextStream oIn(&o);
    QList<QString> compared;
    int oriTotal = 0;
    int oTotal = 0;
    int matched = 0;

    while (!oIn.atEnd())
    {
       compared.push_back(oIn.readLine());
       ++oTotal;
    }

    while (!oriIn.atEnd())
    {
        QString line = oriIn.readLine();
        ++oriTotal;
        QListIterator<QString> it(compared);
        while (it.hasNext())
        {
            if (it.next() == line)
            {
                ++matched;
                break;
            }
        }
    }
    float result = ((float)matched * 100) / ((float)oriTotal + (float)oTotal);
    return result;
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
    return results;
    results.clear();
    for (int i = 0; i < sources.count(); ++i)
    {
        for (int j = i + 1; j < sources.count(); ++j)
        {
            AnalysisResult *res = new AnalysisResult(qrand() % 101, QString::number(i), QString::number(j), QHash<QString, QVariant>());
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

    QLabel *label = new QLabel("This module does not have specific parameters.");
    QPushButton *button = new QPushButton("Ok");
    connect(button, SIGNAL(clicked()), this, SLOT(accept()));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(button, 0, Qt::AlignRight);
    setLayout(layout);
    setWindowTitle("Parameters window");
}
