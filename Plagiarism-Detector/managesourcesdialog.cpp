#include "managesourcesdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

ManageSourcesDialog::ManageSourcesDialog(QWidget *parent, SourceModel *model) :
    QDialog(parent)
{
    this->model = model;

    addFilesButton = new QPushButton(tr("Add Source File(s)..."));
    addFoldersButton = new QPushButton(tr("Add Source Folder(s)..."));
    deleteSourcesButton = new QPushButton(tr("Delete Source(s)"));
    okButton = new QPushButton(tr("Ok"));
    connect(addFilesButton, SIGNAL(clicked()), parent, SLOT(addSourcesFile()));
    connect(addFoldersButton, SIGNAL(clicked()), parent, SLOT(addSourcesFolder()));
    connect(deleteSourcesButton, SIGNAL(clicked()), parent, SLOT(deleteSources()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

    listView = new QListView(this);
    listView->setModel(model);

    QHBoxLayout *sourceButtons = new QHBoxLayout();
    sourceButtons->addWidget(addFilesButton);
    sourceButtons->addWidget(addFoldersButton);
    sourceButtons->addWidget(deleteSourcesButton);

    QVBoxLayout *windowLayout = new QVBoxLayout();
    windowLayout->addWidget(listView);
    windowLayout->addLayout(sourceButtons);
    windowLayout->addWidget(okButton, 0, Qt::AlignRight);
    setLayout(windowLayout);
    setWindowTitle(tr("Manage Sources"));
}
