#include <QtWidgets>

#include "mainwindow.h"
#include "managemoduledialog.h"
#include "managesourcesdialog.h"

MainWindow::MainWindow()
{
    tabWidget = new QTabWidget;
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

//    cutAct = new QAction(tr("Cu&t"), this);
//    cutAct->setShortcuts(QKeySequence::Cut);
//    cutAct->setStatusTip("Cut the current selection to the clipboard");
//    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

//    copyAct = new QAction(tr("&Copy"), this);
//    copyAct->setShortcuts(QKeySequence::Copy);
//    copyAct->setStatusTip("Copy the current selection to the clipboard");
//    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

//    pasteAct = new QAction(tr("&Paste"), this);
//    pasteAct->setShortcuts(QKeySequence::Paste);
//    pasteAct->setStatusTip("Paste the clipboard's contents into the current selection");
//    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

//    undoAct = new QAction(tr("&Undo"), this);
//    undoAct->setShortcuts(QKeySequence::Undo);
//    undoAct->setStatusTip("Undo last action");
//    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

//    redoAct = new QAction(tr("&Redo"), this);
//    redoAct->setShortcuts(QKeySequence::Redo);
//    redoAct->setStatusTip("Redo last action");
//    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    manageModulesAct = new QAction(tr("&Manage Modules..."), this);
    shortcuts = new QList<QKeySequence>();
    shortcuts->append(QKeySequence::fromString("Ctrl+M", QKeySequence::NativeText));
    manageModulesAct->setShortcuts(*shortcuts);
    manageModulesAct->setStatusTip("Open the manage modules window");
    connect(manageModulesAct, SIGNAL(triggered()), this, SLOT(manageModules()));

    configureModuleAct = new QAction(tr("&Configure Module..."), this);
    configureModuleAct->setStatusTip("Open the Configuration window for the selected detection module");
    connect(configureModuleAct, SIGNAL(triggered()), this, SLOT(configureModule()));

    selectModulesAct = new QAction(tr("&Select Modules..."), this);
    //find a shortcut
    //shortcuts = new QList<QKeySequence>();
    //shortcuts->append(QKeySequence::fromString("Ctrl+", QKeySequence::NativeText));
    //newAct->setShortcuts(*shortcuts);
    selectModulesAct->setStatusTip("Open the select modules window");
    connect(selectModulesAct, SIGNAL(triggered()), this, SLOT(selectModules()));

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

//    editMenu = menuBar()->addMenu(tr("&Edit"));
//    editMenu->addAction(cutAct);
//    editMenu->addAction(copyAct);
//    editMenu->addAction(pasteAct);
//    editMenu->addSeparator();
//    editMenu->addAction(undoAct);
//    editMenu->addAction(redoAct);

    modulesMenu = menuBar()->addMenu(tr("&Modules"));
    modulesMenu->addAction(manageModulesAct);
//    modulesMenu->addAction(selectModulesAct);

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
    QPushButton *manMod = new QPushButton(tr("Manage Modules"));
    connect(manMod, SIGNAL(clicked()), this, SLOT(manageModules()));
    QPushButton *configure = new QPushButton(tr("Configure Module"));
    connect(configure, SIGNAL(clicked()), this, SLOT(configureModule()));

    QVBoxLayout *moduleLayout = new QVBoxLayout();
    moduleLayout->addWidget(modulesListView);
    moduleLayout->addWidget(configure);
    moduleLayout->addWidget(manMod);

    //Sources Layout
    sourcesListView = new QListView(configuration);
    sourcesListView->setModel(sources);
    sourcesListView->setSelectionMode(QAbstractItemView::MultiSelection);
    QPushButton *addFile = new QPushButton(tr("Add Source File(s)..."));
    connect(addFile, SIGNAL(clicked()), this, SLOT(addSourcesFile()));
    QPushButton *addFolder = new QPushButton(tr("Add Source Folder(s)..."));
    connect(addFolder, SIGNAL(clicked()), this, SLOT(addSourcesFolder()));
    QPushButton *deleteSource = new QPushButton(tr("Delete Source(s)..."));
    connect(deleteSource, SIGNAL(clicked()), this, SLOT(deleteSources()));

    QHBoxLayout *sourceButtonsLayout = new QHBoxLayout();
    sourceButtonsLayout->addWidget(addFile);
    sourceButtonsLayout->addWidget(addFolder);
    sourceButtonsLayout->addWidget(deleteSource);

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
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
}

void MainWindow::exportResults()
{

}

void MainWindow::quit()
{

}

void MainWindow::cut()
{

}

void MainWindow::copy()
{

}

void MainWindow::paste()
{

}

void MainWindow::undo()
{

}

void MainWindow::redo()
{

}

void MainWindow::manageModules()
{
    ManageModuleDialog *dialog = new ManageModuleDialog(this, modules);
    dialog->exec();
}

void MainWindow::selectModules()
{

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

        for(int i = 0; i < indexes->count(); ++i)
        {
            QModelIndex index = indexes->at(i);
            if (modules->data(index, Qt::CheckStateRole).toBool())
            {
                QObject *obj = qvariant_cast<QObject *>(modules->data(index, Qt::UserRole));
                DetectionModuleInterface *module = qobject_cast<DetectionModuleInterface *>(obj);
                module->setDelegate(this);
                checkedModules.append(module);
            }
        }
        moduleNumber = checkedModules.count();
    }

    if (checkedModules.count())
    {
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
    QModelIndex indexes = modulesListView->selectionModel()->selectedIndexes();
    if (indexes.size())
    {
        QObject *obj = qvariant_cast<QObject *>(modules->data(index, Qt::UserRole));
        DetectionModuleInterface *module = qobject_cast<DetectionModuleInterface *>(obj);
        module->getParameterForm().exec();
    }
}

void MainWindow::statusChanged(int newStatus)
{
    switch (newStatus) {
    case DetectionModuleInterface::started:
        isPaused = false;
        progressBar->setEnabled(true);
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
        progressBar->setEnabled(false);
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
            // create result view
            progressBar->setEnabled(false);
        }
        break;
    default:
        // an error occured somewhere
        break;
    }
}

void MainWindow::progressChanged(int newProgress)
{
    int finished = finishedModules.count();
    int onGoing = checkedModules.count();
    int total = finished + onGoing;
    progressBar->setValue((100 / total * finished) + (newProgress * 100 / total));
}
