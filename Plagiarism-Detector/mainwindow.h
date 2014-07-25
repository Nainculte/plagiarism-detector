#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QMenu>
#include <QPushButton>
#include <QListWidgetItem>
#include <QLabel>
#include <QProgressBar>
#include <QAction>
#include "sourcemodel.h"
#include "modulemodel.h"
#include "DetectionModuleInterface.h"
#include "DetectionModuleHolder.h"

class MainWindow : public QMainWindow, public DetectionModuleHolder
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

    void statusChanged(int newStatus);
    void progressChanged(int newProgress);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void exportResults();
    void quit();
    void cut();
    void copy();
    void paste();
    void undo();
    void redo();
    void manageModules();
    void selectModules();
    void manageSources();
    void selectSourcesSkeleton();
    void startResume();
    void pause();
    void stop();
    void about();
    void documentation();

public slots:
    void configureModule();
    void addSourcesFile();
    void addSourcesFolder();
    void deleteSources();

private:
    void createActions();
    void createMenus();
    void initConfigurationView();

    QTabWidget *tabWidget;
    QLabel *statusLabel;
    QProgressBar *progressBar;
    QWidget *configuration;
    QList<QWidget> *results;
    QListView *sourcesListView;
    QListView *modulesListView;

    ModuleModel *modules;
    SourceModel *sources;

    bool isPaused;

    DetectionModuleInterface *currentModule;
    QList<DetectionModuleInterface *>checkedModules;
    QList<DetectionModuleInterface *>finishedModules;

    int moduleNumber;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *modulesMenu;
    QMenu *sourcesMenu;
    QMenu *analysisMenu;
    QMenu *helpMenu;

    QAction *exportAct;
    QAction *quitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *manageModulesAct;
    QAction *configureModuleAct;
    QAction *selectModulesAct;
    QAction *addSourcesFolderAct;
    QAction *addSourcesFileAct;
    QAction *manageSourcesAct;
    QAction *selectSourcesSkeletonAct;
    QAction *startResumeAct;
    QAction *pauseAct;
    QAction *stopAct;
    QAction *aboutAct;
    QAction *documentationAct;
};

#endif // MAINWINDOW_H
