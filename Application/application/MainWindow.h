#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QMessageBox>
#include "WindowManager.h"
#include "FileDialog.h"

/**
 * Class of main window in application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow();
    ~MainWindow();
private:
    QWidget* mCentralWidget;
    QVBoxLayout* mLayout;

    // Menu
    QMenuBar* mMenuBar;
    QMenu* mMenuFile;
    QMenu* mMenuPlot;

    // Menu actions
    QAction* mActionFileOpen;
    QAction* mActionPlotLine;
    QAction* mActionPlotHistogram;

    WindowManager & mWindowManager;
    FileDialog mFileDialog;

private slots:

    /// Action executed when user press "Open file" action.
    void onOpenFile();

    /// Action executed when user press "Plot line" action.
    void onPlotLine();

    /// Action executed when user press "Histogram" action.
    void onPlotHistogram();

};

#endif // MAINWINDOW_H
