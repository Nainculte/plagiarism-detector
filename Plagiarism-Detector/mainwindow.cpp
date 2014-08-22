#include <QtWidgets>

#include "mainwindow.h"
#include "managemoduledialog.h"
#include "managesourcesdialog.h"
#include "quitdialog.h"
#include "moduleresultwrapper.h"
#include "resultmodel.h"

MainWindow::MainWindow()
{
    tabWidget = new QTabWidget;
    tabWidget->setTabsClosable(true);
    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    setCentralWidget(tabWidget);

    modules = new ModuleModel();
    sources = new SourceModel();

    isPaused = false;

    createActions();
    createMenus();
    initConfigurationView();
}

void MainWindow::createActions()
{
    QList<QKeySequence> *shortcuts;

    exportAct = new QAction(tr("&Export..."), this);
    shortcuts = new QList<QKeySequence>();
    shortcuts->append(QKeySequence::fromString("Ctrl+E", QKeySequence::NativeText));
    exportAct->setShortcuts(*shortcuts);
    exportAct->setStatusTip("Exports the results");
    connect(exportAct, SIGNAL(triggered()), this, SLOT(exportResults()));

    quitAct = new QAction(tr("&Exit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip("Quit the application");
    connect(quitAct, SIGNAL(triggered()), this, SLOT(quit()));

    manageModulesAct = new QAction(tr("&Manage Modules..."), this);
    shortcuts = new QList<QKeySequence>();
    shortcuts->append(QKeySequence::fromString("Ctrl+M", QKeySequence::NativeText));
    manageModulesAct->setShortcuts(*shortcuts);
    manageModulesAct->setStatusTip("Open the manage modules window");
    connect(manageModulesAct, SIGNAL(triggered()), this, SLOT(manageModules()));

    configureModuleAct = new QAction(tr("&Configure Module..."), this);
    configureModuleAct->setStatusTip("Open the Configuration window for the selected detection module");
    connect(configureModuleAct, SIGNAL(triggered()), this, SLOT(configureModule()));

    addSourcesFolderAct = new QAction(tr("Add &Sources Folders..."), this);
    // find a shortcut
    //shortcuts = new QList<QKeySequence>();
    //shortcuts->append(QKeySequence::fromString("Ctrl+", QKeySequence::NativeText));
    //newAct->setShortcuts(*shortcuts);
    addSourcesFolderAct->setStatusTip("Add project folder(s) to test");
    connect(addSourcesFolderAct, SIGNAL(triggered()), this, SLOT(addSourcesFolder()));

    addSourcesFileAct = new QAction(tr("Add Sources &Files..."), this);
    // find a shortcut
    //shortcuts = new QList<QKeySequence>();
    //shortcuts->append(QKeySequence::fromString("Ctrl+", QKeySequence::NativeText));
    //newAct->setShortcuts(*shortcuts);
    addSourcesFileAct->setStatusTip("Add project file(s) to test");
    connect(addSourcesFileAct, SIGNAL(triggered()), this, SLOT(addSourcesFile()));

    manageSourcesAct = new QAction(tr("&Manage Sources..."), this);
    // find a shortcut
    //shortcuts = new QList<QKeySequence>();
    //shortcuts->append(QKeySequence::fromString("Ctrl+", QKeySequence::NativeText));
    //newAct->setShortcuts(*shortcuts);
    manageSourcesAct->setStatusTip("Open the manage sources window");
    connect(manageSourcesAct, SIGNAL(triggered()), this, SLOT(manageSources()));

    selectSourcesSkeletonAct = new QAction(tr("Select Sources S&keleton..."), this);
    // find a shortcut
    //shortcuts = new QList<QKeySequence>();
    //shortcuts->append(QKeySequence::fromString("Ctrl+", QKeySequence::NativeText));
    //newAct->setShortcuts(*shortcuts);
    selectSourcesSkeletonAct->setStatusTip("Open the project skeleton manager window");
    connect(selectSourcesSkeletonAct, SIGNAL(triggered()), this, SLOT(selectSourcesSkeleton()));

    startResumeAct = new QAction(tr("&Start / Resume"), this);
    shortcuts = new QList<QKeySequence>();
    shortcuts->append(QKeySequence::fromString("Ctrl+R", QKeySequence::NativeText));
    startResumeAct->setShortcuts(*shortcuts);
    startResumeAct->setStatusTip("Start / resume the analysis");
    connect(startResumeAct, SIGNAL(triggered()), this, SLOT(startResume()));

    pauseAct = new QAction(tr("&Pause"), this);
    shortcuts = new QList<QKeySequence>();
    shortcuts->append(QKeySequence::fromString("Ctrl+P", QKeySequence::NativeText));
    pauseAct->setShortcuts(*shortcuts);
    pauseAct->setStatusTip("Pause the analysis");
    connect(pauseAct, SIGNAL(triggered()), this, SLOT(pause()));

    stopAct = new QAction(tr("S&top"), this);
    shortcuts = new QList<QKeySequence>();
    shortcuts->append(QKeySequence::fromString("Ctrl+S", QKeySequence::NativeText));
    stopAct->setShortcuts(*shortcuts);
    stopAct->setStatusTip("Stop the analysis");
    connect(stopAct, SIGNAL(triggered()), this, SLOT(stop()));

    aboutAct = new QAction(tr("&About Plagiarism-Detector"), this);
    aboutAct->setStatusTip("Show the about window");
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    documentationAct = new QAction(tr("&Documentation"), this);
    documentationAct->setStatusTip("Show the documentation window");
    connect(documentationAct, SIGNAL(triggered()), this, SLOT(documentation()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exportAct);
    fileMenu->addAction(quitAct);

    modulesMenu = menuBar()->addMenu(tr("&Modules"));
    modulesMenu->addAction(manageModulesAct);

    sourcesMenu = menuBar()->addMenu(tr("&Sources"));
    sourcesMenu->addAction(addSourcesFileAct);
    sourcesMenu->addAction(addSourcesFolderAct);
    sourcesMenu->addAction(manageSourcesAct);
    sourcesMenu->addSeparator();
    sourcesMenu->addAction(selectSourcesSkeletonAct);

    analysisMenu = menuBar()->addMenu(tr("&Analysis"));
    analysisMenu->addAction(startResumeAct);
    analysisMenu->addAction(pauseAct);
    analysisMenu->addAction(stopAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(documentationAct);
}

void MainWindow::initConfigurationView()
{
    configuration = new QWidget(this);

    //Module layout
    modulesListView = new QListView(configuration);
    modulesListView->setModel(modules);
    manageModulesButton = new QPushButton(tr("Manage Modules"));
    connect(manageModulesButton, SIGNAL(clicked()), this, SLOT(manageModules()));
    configureModuleButton = new QPushButton(tr("Configure Module"));
    connect(configureModuleButton, SIGNAL(clicked()), this, SLOT(configureModule()));

    QVBoxLayout *moduleLayout = new QVBoxLayout();
    moduleLayout->addWidget(modulesListView);
    moduleLayout->addWidget(configureModuleButton);
    moduleLayout->addWidget(manageModulesButton);

    //Sources Layout
    sourcesListView = new QListView(configuration);
    sourcesListView->setModel(sources);
    sourcesListView->setSelectionMode(QAbstractItemView::MultiSelection);
    addFilesButton = new QPushButton(tr("Add Source File(s)..."));
    connect(addFilesButton, SIGNAL(clicked()), this, SLOT(addSourcesFile()));
    addFoldersButton = new QPushButton(tr("Add Source Folder(s)..."));
    connect(addFoldersButton, SIGNAL(clicked()), this, SLOT(addSourcesFolder()));
    deleteSourcesButton = new QPushButton(tr("Delete Source(s)..."));
    connect(deleteSourcesButton, SIGNAL(clicked()), this, SLOT(deleteSources()));

    QHBoxLayout *sourceButtonsLayout = new QHBoxLayout();
    sourceButtonsLayout->addWidget(addFilesButton);
    sourceButtonsLayout->addWidget(addFoldersButton);
    sourceButtonsLayout->addWidget(deleteSourcesButton);

    QVBoxLayout *sourceLayout = new QVBoxLayout();
    sourceLayout->addWidget(sourcesListView);
    sourceLayout->addLayout(sourceButtonsLayout);

    //Analysis layout
    QPushButton *startResumeButton = new QPushButton(tr("Start / Resume"));
    connect(startResumeButton, SIGNAL(clicked()), this, SLOT(startResume()));
    QPushButton *pauseButton = new QPushButton(tr("Pause"));
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    QPushButton *stopButton = new QPushButton(tr("Stop"));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    statusLabel = new QLabel("Waiting");

    QHBoxLayout *analysisButtonsLayout = new QHBoxLayout();
    analysisButtonsLayout->addWidget(startResumeButton);
    analysisButtonsLayout->addWidget(pauseButton);
    analysisButtonsLayout->addWidget(stopButton);
    analysisButtonsLayout->addWidget(statusLabel);

    progressBar = new QProgressBar();
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);

    //Source & Analysis layout
    QVBoxLayout *sourceAnalysis = new QVBoxLayout();
    sourceAnalysis->addLayout(sourceLayout);
    sourceAnalysis->addLayout(analysisButtonsLayout);
    sourceAnalysis->addWidget(progressBar);

    //Window layout
    QHBoxLayout *windowLayout = new QHBoxLayout();
    windowLayout->addLayout(moduleLayout);
    windowLayout->addLayout(sourceAnalysis);

    configuration->setLayout(windowLayout);

    tabWidget->addTab(configuration, tr("Configuration"));

    if (tabWidget->tabBar()->tabButton(0, QTabBar::RightSide))
        tabWidget->tabBar()->tabButton(0, QTabBar::RightSide)->resize(0, 0);
    else
        tabWidget->tabBar()->tabButton(0, QTabBar::LeftSide)->resize(0, 0);
}

void MainWindow::createResultView()
{
    QWidget *result = new QWidget(this);
    results.append(result);
    tabWidget->addTab(result, "Result " + QDateTime::currentDateTime().toString("dd/mm/yyyy hh:mm"));

    QList<ModuleResultWrapper> wrappers;
    foreach (DetectionModuleInterface *module, finishedModules) {
        ModuleResultWrapper *wrapper = new ModuleResultWrapper(module, module->getAnalysisResults());
        wrappers << *wrapper;
    }
    ResultModel *model = new ResultModel(wrappers,
                                         sources->getSources().count(),
                                         this);
    QListView *sideView = new QListView(result);
    sideView->setModel(model);
    QTableView *tableView = new QTableView(result);
    tableView->setModel(model);
    tableView->setRootIndex(model->tableIndexForRow(0));
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(sideView);
    layout->addWidget(tableView, 2);
    result->setLayout(layout);
    tabWidget->setCurrentIndex(results.count());
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (analisysRunning)
    {
        QuitDialog *dialog = new QuitDialog(this);
        if (dialog->exec())
        {
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
    else
    {
        event->accept();
    }
}

void MainWindow::exportResults()
{

}

void MainWindow::quit()
{
    close();
}

void MainWindow::manageModules()
{
    ManageModuleDialog *dialog = new ManageModuleDialog(this, modules);
    dialog->exec();
}

void MainWindow::addSourcesFile()
{
    QFileDialog dialog(this);
    dialog.setDirectory(QStandardPaths::locate(QStandardPaths::DocumentsLocation, "", QStandardPaths::LocateDirectory));
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setOption(QFileDialog::ReadOnly, true);
    QStringList fileNames;
    if (dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        sources->insertRows(0, fileNames.count(), QModelIndex());

        for (int i = 0; i < fileNames.count(); ++i)
        {
            QModelIndex index = sources->index(i, 0, QModelIndex());
            sources->setData(index, fileNames.at(i), Qt::EditRole);
            sources->setData(index, true, Qt::DecorationRole);
        }
    }
}

void MainWindow::addSourcesFolder()
{
    QFileDialog dialog(this);
    dialog.setDirectory(QStandardPaths::locate(QStandardPaths::DocumentsLocation, "", QStandardPaths::LocateDirectory));
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ReadOnly, true);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    QStringList fileNames;
    if (dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        sources->insertRows(0, fileNames.count(), QModelIndex());

        for (int i = 0; i < fileNames.count(); ++i)
        {
            QModelIndex index = sources->index(i, 0, QModelIndex());
            sources->setData(index, fileNames.at(i), Qt::EditRole);
            sources->setData(index, false, Qt::DecorationRole);
        }
    }
}

void MainWindow::deleteSources()
{
    QModelIndexList indexes;
    while((indexes = sourcesListView->selectionModel()->selectedIndexes()).size()) {
        sources->removeRows(indexes.first().row(), 1, QModelIndex());
    }
}

void MainWindow::manageSources()
{
    ManageSourcesDialog *dialog = new ManageSourcesDialog(this, sources);
    dialog->exec();
}

void MainWindow::selectSourcesSkeleton()
{

}

void MainWindow::startResume()
{
    if (!isPaused)
    {
        // start
        QModelIndexList *indexes = new QModelIndexList();
        for (int i = 0; i < modules->rowCount(QModelIndex()); ++i)
            indexes->append(modules->index(i, 0));

        if (!indexes->count())
        {
            QMessageBox::warning(this, "Warning", "Add at least a detection module to start");
            return;
        }
        checkedModules.clear();
        finishedModules.clear();
        for(int i = 0; i < indexes->count(); ++i)
        {
            QModelIndex index = indexes->at(i);
            if (modules->data(index, Qt::CheckStateRole).toBool())
            {
                QObject *obj = qvariant_cast<QObject *>(modules->data(index, Qt::UserRole));
                DetectionModuleInterface *module = qobject_cast<DetectionModuleInterface *>(obj);
                module->setDelegate(this);
                module->setSources(sources->getSources());
                checkedModules.append(module);
            }
        }
        moduleNumber = checkedModules.count();
    }

    if (checkedModules.count())
    {
        modulesListView->setEnabled(false);
        sourcesListView->setEnabled(false);
        currentModule = checkedModules.first();
        currentModule->startAnalysis();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Please check at least one detection Module");
    }
}

void MainWindow::pause()
{
    currentModule->pauseAnalysis();
}

void MainWindow::stop()
{
    currentModule->stopAnalysis();
    checkedModules.clear();
    finishedModules.clear();
}

void MainWindow::about()
{
    QMessageBox::about(this, "About Plagiarism-Detector",
                       "<h1 align='center'>Plagiarism-Detector</h1>"
                       "<p align ='center'>Version 0.0.1<br>"
                       "Developped by:</p>"
                       "<h2 align='center'>Antoine Jacquin-Ravot</h2>"
                       "<p align='center'>&</p>"
                       "<h2 align='center'>Olivier Duménil<h2>");
}

void MainWindow::documentation()
{

}

void MainWindow::configureModule()
{
    QModelIndexList indexes = modulesListView->selectionModel()->selectedIndexes();
    if (indexes.size())
    {
        QObject *obj = qvariant_cast<QObject *>(modules->data(indexes.first(), Qt::UserRole));
        DetectionModuleInterface *module = qobject_cast<DetectionModuleInterface *>(obj);
        module->getParameterForm().exec();
    }
}

void MainWindow::statusChanged(int newStatus)
{
    switch (newStatus) {
    case DetectionModuleInterface::started:
        isPaused = false;
        analisysRunning = true;
        progressBar->setEnabled(true);
        lockUserInterface();
        break;
    case DetectionModuleInterface::resumed:
        isPaused = false;
        progressBar->setEnabled(true);
        break;
    case DetectionModuleInterface::paused:
        isPaused = true;
        progressBar->setEnabled(false);
        break;
    case DetectionModuleInterface::stopped:
        isPaused = false;
        analisysRunning = false;
        progressBar->setEnabled(false);
        unlockUserInterface();
        break;
    case DetectionModuleInterface::finished:
        // get current module results or add the module to a list of finished modules
        finishedModules.append(checkedModules.first());
        checkedModules.pop_front();
        if (checkedModules.count())
        {
            currentModule = checkedModules.first();
            currentModule->startAnalysis();
        }
        else
        {
            createResultView();
            progressBar->setEnabled(false);
            unlockUserInterface();
            analisysRunning = false;
        }
        break;
    default:
        // an error occured somewhere
        unlockUserInterface();
        break;
    }
}

void MainWindow::progressChanged(int newProgress)
{
    int finished = finishedModules.count();
    int onGoing = checkedModules.count();
    int total = finished + onGoing;
    progressBar->setValue((100 / total * finished) + (newProgress * (100 / total)));
}

void MainWindow::lockUserInterface()
{
    sourcesListView->setEnabled(false);
    modulesListView->setEnabled(false);
    manageModulesAct->setEnabled(false);
    configureModuleAct->setEnabled(false);
    addSourcesFileAct->setEnabled(false);
    addSourcesFolderAct->setEnabled(false);
    manageSourcesAct->setEnabled(false);
    deleteSourcesButton->setEnabled(false);
    selectSourcesSkeletonAct->setEnabled(false);
}

void MainWindow::unlockUserInterface()
{
    sourcesListView->setEnabled(true);
    modulesListView->setEnabled(true);
    manageModulesAct->setEnabled(true);
    configureModuleAct->setEnabled(true);
    addSourcesFileAct->setEnabled(true);
    addSourcesFolderAct->setEnabled(true);
    manageSourcesAct->setEnabled(true);
    deleteSourcesButton->setEnabled(true);
    selectSourcesSkeletonAct->setEnabled(true);
}

void MainWindow::closeTab(int index)
{
    if (index == -1 || index == 0)
        return;

    QWidget *tab = tabWidget->widget(index);
    tabWidget->removeTab(index);
    results.removeAt(index - 1);
    delete(tab);
    tab = Q_NULLPTR;
}
