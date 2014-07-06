#include "managemoduledialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QStandardPaths>

ManageModuleDialog::ManageModuleDialog(QWidget *parent, ModuleModel *model) :
    QDialog(parent)
{
    this->model = model;
    addModuleAct = new QAction(tr("&Add Modules..."), this);
    addModuleAct->setStatusTip("Open a file browser to add new detection modules");
    deleteModuleAct = new QAction(tr("%Delete Module"), this);
    deleteModuleAct->setStatusTip("Delete the selected module");

    listView = new QListView();
    addModuleButton = new QPushButton(tr("Add Module(s)..."));
    deleteModuleButton = new QPushButton(tr("Delete Module"));
    configureModuleButton = new QPushButton(tr("Configure Module"));
    okButton = new QPushButton(tr("Ok"));

    QVBoxLayout *windowLayout = new QVBoxLayout();
    listView->setModel(model);
    windowLayout->addWidget(listView);

    QHBoxLayout *moduleButtons = new QHBoxLayout();
    moduleButtons->addWidget(addModuleButton);
    moduleButtons->addWidget(deleteModuleButton);
    moduleButtons->addWidget(configureModuleButton);

    windowLayout->addLayout(moduleButtons);
    windowLayout->addWidget(okButton, 0, Qt::AlignRight);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(addModuleButton, SIGNAL(clicked()), this, SLOT(addModule()));
    connect(deleteModuleButton, SIGNAL(clicked()), this, SLOT(deleteModule()));
    connect(configureModuleButton, SIGNAL(clicked()), parent, SLOT(configureModule()));

    setLayout(windowLayout);
    setWindowTitle(tr("Manage Modules"));
}

void ManageModuleDialog::addModule()
{
    QFileDialog dialog(this);
    dialog.setDirectory(QStandardPaths::locate(QStandardPaths::DocumentsLocation, "", QStandardPaths::LocateDirectory));
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setOption(QFileDialog::ReadOnly, true);
    QStringList fileNames;
    if (dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        model->insertRows(0, fileNames.count(), QModelIndex());

        for (int i = 0; i < fileNames.count(); ++i)
        {
            QModelIndex index = model->index(i, 0, QModelIndex());
            model->setData(index, fileNames.at(i), Qt::EditRole);
        }
    }
}

void ManageModuleDialog::deleteModule()
{
    QItemSelectionModel *selectionModel = listView->selectionModel();
    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes) {
        model->removeRows(index.row(), 1, QModelIndex());
    }
}
