#ifndef MANAGEMODULEDIALOG_H
#define MANAGEMODULEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QListView>
#include <QAction>
#include "modulemodel.h"

class ManageModuleDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ManageModuleDialog(QWidget *parent, ModuleModel *model);

private:
    QListView *listView;
    QPushButton *addModuleButton;
    QPushButton *deleteModuleButton;
    QPushButton *configureModuleButton;
    QPushButton *okButton;

    QAction *addModuleAct;
    QAction *deleteModuleAct;

    ModuleModel *model;

private slots:
    void addModule();
    void deleteModule();
    void configureModule();

};

#endif // MANAGEMODULEDIALOG_H
