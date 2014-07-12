#ifndef MANAGESOURCESDIALOG_H
#define MANAGESOURCESDIALOG_H

#include <QDialog>
#include <QListView>
#include <QPushButton>
#include <QAction>
#include "sourcemodel.h"

class ManageSourcesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ManageSourcesDialog(QWidget *parent, SourceModel *model);

private:
    QListView *listView;
    QPushButton *addFilesButton;
    QPushButton *addFoldersButton;
    QPushButton *deleteSourcesButton;
    QPushButton *okButton;

    SourceModel *model;

};

#endif // MANAGESOURCESDIALOG_H
