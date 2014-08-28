#include "managemoduledialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QPluginLoader>
#include <QObject>
#include "DetectionModuleInterface.h"

ManageModuleDialog::ManageModuleDialog(QWidget *parent, ModuleModel *model) :
    QDialog(parent)
{
    this->model = model;
    addModuleAct = new QAction(tr("&Add Modules..."), this);
    addModuleAct->setStatusTip("Open a file browser to add new detection modules");
    deleteModuleAct = new QAction(tr("%Delete Module"), this);
    deleteModuleAct->setStatusTip("Delete the selected module");

    listView = new QListView();
    addModuleButton = new QPushButton(tr("Add Module..."));
    deleteModuleButton = new QPushButton(tr("Delete Module"));
    configureModuleButton = new QPushButton(tr("Configure Module..."));
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
    connect(configureModuleButton, SIGNAL(clicked()), this, SLOT(configureModule()));

    setLayout(windowLayout);
    setWindowTitle(tr("Manage Modules"));
}

void ManageModuleDialog::addModule()
{
    QFileDialog dialog(this);
    dialog.setDirectory(QStandardPaths::locate(QStandardPaths::DocumentsLocation, "", QStandardPaths::LocateDirectory));
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setOption(QFileDialog::ReadOnly, true);
    QStringList fileNames;
    if (dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        QString name = fileNames.at(0);
        QPluginLoader loader(name);
        QObject *plug = loader.instance();
        if (plug)
        {
            DetectionModuleInterface *plugin = qobject_cast<DetectionModuleInterface *>(plug);
            if (plugin)
            {
                model->insertRows(0, 1, QModelIndex());
                QModelIndex index = model->index(0, 0, QModelIndex());
                model->setData(index, plugin->getModuleInformation(), Qt::EditRole);
                model->setData(index, qVariantFromValue(plug), Qt::UserRole);
            }
            else
            {
                QMessageBox::warning(this, "Detection module", "Selected file is not a valid detection module.");
            }
        }
        else
        {
            QMessageBox::warning(this, "Detection module", "Selected file is not a valid detection module.");
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

void ManageModuleDialog::configureModule()
{
    QModelIndexList indexes = listView->selectionModel()->selectedIndexes();
    if (indexes.size())
    {
        QObject *obj = qvariant_cast<QObject *>(model->data(indexes.first(), Qt::UserRole));
        DetectionModuleInterface *module = qobject_cast<DetectionModuleInterface *>(obj);
        module->getParameterForm().exec();
    }
}
