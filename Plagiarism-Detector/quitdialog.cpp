#include "quitdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

QuitDialog::QuitDialog(QWidget *parent) :
    QDialog(parent)
{
    QPushButton *quitAnyway = new QPushButton(tr("Quit Anyway"));
    QPushButton *cancel = new QPushButton (tr("Cancel"));
    QLabel *message = new QLabel(tr("The analysis has not completed yet.\nQuit anyway?"));

    connect(quitAnyway, SIGNAL(clicked()), parent, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), parent, SLOT(reject()));

    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addWidget(quitAnyway);
    buttons->addWidget(cancel);

    QVBoxLayout *window = new QVBoxLayout();
    window->addWidget(message);
    window->addLayout(buttons);

    setLayout(window);
    setWindowTitle(tr("We have not finished working here..."));
}
