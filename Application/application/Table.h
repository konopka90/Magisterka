#ifndef TABLE_H
#define TABLE_H

#include <QTableView>
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QMenu>
#include "Window.h"
#include "TableModel.h"
#include "TableView.h"

class Table : public Window
{
    Q_OBJECT
public:
    explicit Table(QWidget *parent = 0);
    ~Table();

    Table(QString filename, QWidget *parent = 0);
    const TableModel & model() const;
    const TableView & view() const;

private:

    TableView * mTableView;
    TableModel * mTableViewModel;
    QMenu mColumnMenu;



private:

    void initCommon();
    bool isMemoryAvailable(int rows, int cols);
    void showContextMenuColumn(const QPoint&);
    void setTypeForSelectedColumns(TableColumn::ColumnType colType);

signals:

    //void customContextMenuRequest(QPoint)
    void menuPlotLineClicked();
    void menuPlotHistogramClicked();
    void menuSetAsXClicked();
    void menuSetAsYClicked();
    
public slots:

    void onMenuSetAsXClick();
    void onMenuSetAsYClick();
    void onMenuPlotLineClick();
    void onMenuPlotHistogramClick();
    void onCustomContextMenuRequestedHorizontal(QPoint);
    

};

#endif // TABLE_H
