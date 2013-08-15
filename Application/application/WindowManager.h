#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QMdiArea>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QList>
#include <boost/shared_ptr.hpp>

#include "Window.h"
#include "Table.h"
#include "PlotLine.h"
#include "PlotHistogram.h"
#include "PlotDialog.h"

struct ColumnPair
{
    int columnX;
    QVector<int> columnsY;
};

typedef QList<ColumnPair> ColumnPairsList;

class ColumnComparator
{
public:
    ColumnComparator(const Table& table )
        : mTable(table)
    {   }

    bool operator()(QModelIndex& a, QModelIndex& b)
    {
        return mTable.view().horizontalHeader()->visualIndex(a.column()) <
               mTable.view().horizontalHeader()->visualIndex(b.column());
    }

private:

    const Table & mTable;
\
};

class WindowManager : QWidget
{
    Q_OBJECT
public:

    static WindowManager & getInstance(QWidget * parent);
    QMdiArea * getArea() const;
    void createEmptyTable();
    void createTableFromFile(const QString& filename);

    Q_INVOKABLE void plotLine();
    Q_INVOKABLE void plotHistogram();

private:

    WindowManager();
    WindowManager(QWidget *parent);
    WindowManager & operator=(const WindowManager&);
    WindowManager(const WindowManager&);

    inline const Table& getActiveTable() throw(std::bad_cast);

    ColumnPairsList getPlotPairs(const Table & table);
    void initTable(Table * table);
    bool addCurveToPlot(const Table& table, PlotLine* plotLine, int colX, int colY);

    void showNoTableActivatedError();

private:
    QMdiArea * mMdiArea;
};

#endif // WINDOWMANAGER_H
