#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(this)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonApply_clicked()
{
    int rows = ui->spinBoxRows->value();
    int cols = ui->spinBoxColumns->value();
    model.loadData(cols,rows);
    ui->tableView->setModel(&model);
}

void MainWindow::on_spinBoxColumns_editingFinished()
{
    if(ui->spinBoxColumns->hasFocus())
    {
        emit on_buttonApply_clicked();
    }
}

void MainWindow::on_spinBoxRows_editingFinished()
{
    if(ui->spinBoxRows->hasFocus())
    {
        emit on_buttonApply_clicked();
    }
}
