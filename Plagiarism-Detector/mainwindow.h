#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QMenu>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

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
    void addSourcesFile();
    void addSourcesFolder();
    void manageSources();
    void selectSourcesSkeleton();
    void startResume();
    void pause();
    void stop();
    void about();
    void documentation();

private:
    void createActions();
    void createMenus();
    void initConfigurationView();

    QTabWidget *tabWidget;

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
