#include "MainWindow.h"

MainWindow::MainWindow()
    : QMainWindow(),
      mCentralWidget(new QWidget(this)),
      mWindowManager(WindowManager::getInstance(mCentralWidget))
{

    mLayout = new QVBoxLayout(mCentralWidget);
    mCentralWidget->setLayout(mLayout);

    // Menu bar

    mMenuBar = new QMenuBar(mCentralWidget);
    mMenuFile = new QMenu("File",mMenuBar);
    mMenuPlot = new QMenu("Plot",mMenuBar);

    mActionFileOpen = new QAction(tr("Open"),mMenuFile);
    mActionPlotLine = new QAction(tr("Line"),mMenuPlot);
    mActionPlotHistogram = new QAction(tr("Histogram"),mMenuPlot);

    mMenuFile->addAction(mActionFileOpen);
    mMenuPlot->addAction(mActionPlotLine);
    mMenuPlot->addAction(mActionPlotHistogram);

    mMenuBar->addMenu(mMenuFile);
    mMenuBar->addMenu(mMenuPlot);


    // Main window

    mLayout->addWidget(mMenuBar);
    mLayout->addWidget(mWindowManager.getArea());
    mLayout->setMargin(0);

    setWindowTitle(QString("DAQ"));
    setCentralWidget(mCentralWidget);
    showMaximized();

    // Events

    connect(mActionFileOpen,SIGNAL(triggered()),this,SLOT(onOpenFile()));
    connect(mActionPlotLine,SIGNAL(triggered()),this,SLOT(onPlotLine()));
    connect(mActionPlotHistogram,SIGNAL(triggered()),this,SLOT(onPlotHistogram()));

    // Init

    mWindowManager.createEmptyTable();

}

MainWindow::~MainWindow()
{
}

void MainWindow::onOpenFile()
{
    QString file = mFileDialog.openFile();
    if(mFileDialog.isGood())
    {
        mWindowManager.createTableFromFile(file);
    }
}

void MainWindow::onPlotLine()
{
    mWindowManager.plotLine();
}

void MainWindow::onPlotHistogram()
{
    mWindowManager.plotHistogram();
}
