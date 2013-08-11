#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mymodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_buttonApply_clicked();

    void on_spinBoxColumns_editingFinished();

    void on_spinBoxRows_editingFinished();

private:
    Ui::MainWindow *ui;
    MyModel model;
};

#endif // MAINWINDOW_H
