#include "Table.h"

/* [NOTE]
 * Proste przenoszenie kolumn ---> mTableView->horizontalHeader()->moveSection(0,1);
 */

Table::Table(QWidget *parent) :
    Window(parent)
{
    mTableViewModel = new TableModel(this);
    initCommon();
}


Table::Table(QString filename, QWidget *parent) :
    Window(parent)
{
    // File exists ?

    QFile file(filename);
    if(!file.exists())
    {
        qDebug("File not exists.");
        return;
    }

    // Is able to open ?

    bool ok = file.open(QIODevice::ReadOnly);
    if(!ok)
    {
        qDebug("Can not open file.");
        return;
    }

    // Read file

    int cols = 0;
    int rows = 0;
    QTextStream in(&file);

    // Read cols

    QString line = in.readLine();
    QStringList strList = line.split("\t");
    cols = strList.count();

    // Read rows

    in.seek(0);

    while(!in.atEnd())
    {
        line = in.readLine();
        rows++;
    }

    //bool isAvailable = isMemoryAvailable(rows,cols);

    mTableViewModel = new TableModel(this,rows,cols);

    // Fill with data

    int tmpRow = 0;
    int tmpCol = 0;
    double value = 0;
    bool isOK = false;
    QStringList::ConstIterator it;

    in.seek(0);

    // Read file
    while(!in.atEnd())
    {
        tmpCol = 0;
        line = in.readLine();
        strList = line.split("\t");

        it = strList.constBegin();
        while(it!=strList.constEnd())
        {
            value = (*it).toDouble(&isOK);
            if(isOK)
            {
                mTableViewModel->setValue(tmpRow, tmpCol, value);
            }
            it++;
            tmpCol++;
        }

        tmpRow++;
    }

    initCommon();

}

Table::~Table()
{
    delete mTableView;
}

const TableModel & Table::model() const
{
    return *mTableViewModel;
}

const TableView & Table::view() const
{
    return *mTableView;
}

void Table::initCommon()
{
    // Create TableView

    mTableView = new TableView(this);
    mTableView->setModel(mTableViewModel);
    mTableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    mTableView->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);

    // Create menu

    QAction * setAsX = new QAction("Set as X",&mColumnMenu);
    QAction * setAsY = new QAction("Set as Y",&mColumnMenu);
    QAction * plotLine = new QAction("Plot line",&mColumnMenu);
    QAction * plotHistogram = new QAction("Plot histogram",&mColumnMenu);
    mColumnMenu.addAction(setAsX);
    mColumnMenu.addAction(setAsY);
    mColumnMenu.addAction(plotLine);
    mColumnMenu.addAction(plotHistogram);

    setWidget(mTableView);
    resize(QSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT));

    // Events

    connect(mTableView->horizontalHeader(),SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onCustomContextMenuRequestedHorizontal(QPoint)));

    connect(setAsX,SIGNAL(triggered()), this, SLOT(onMenuSetAsXClick()));
    connect(setAsY,SIGNAL(triggered()), this, SLOT(onMenuSetAsYClick()));
    connect(plotLine,SIGNAL(triggered()), this, SLOT(onMenuPlotLineClick()));
    connect(plotHistogram,SIGNAL(triggered()), this, SLOT(onMenuPlotHistogramClick()));

}

bool Table::isMemoryAvailable(int rows, int cols)
{
    int size = rows * cols;

    double * tempData;
    try
    {
        tempData = new double[size];
    }
    catch(std::bad_alloc & ba)
    {
        return false;
    }

    delete [] tempData;

    return true;
}

void Table::showContextMenuColumn(const QPoint& point)
{
    mColumnMenu.exec(point);
}

void Table::setTypeForSelectedColumns(TableColumn::ColumnType colType)
{
    const QVector<TableColumn*> vec = mTableViewModel->columns();
    QModelIndexList list = mTableView->selectionModel()->selectedColumns();
    foreach(QModelIndex modelIndex, list)
    {
        int index = modelIndex.column();
        vec[index]->setType(colType);
    }

    mTableView->horizontalHeader()->hide();
    mTableView->horizontalHeader()->show();


}

void Table::onMenuPlotLineClick()
{
    emit menuPlotLineClicked();
}

void Table::onMenuPlotHistogramClick()
{
    emit menuPlotHistogramClicked();
}

void Table::onMenuSetAsXClick()
{
    setTypeForSelectedColumns(TableColumn::X);
}

void Table::onMenuSetAsYClick()
{
    setTypeForSelectedColumns(TableColumn::Y);
}

void Table::onCustomContextMenuRequestedHorizontal(QPoint point)
{
    // Clicked column
    int index = mTableView->columnAt(point.x());

    // Get currently selected columns
    QModelIndexList list = mTableView->selectionModel()->selectedColumns();

    QList<int> indexes;

    foreach(QModelIndex modelIndex, list)
    {
        indexes.append(modelIndex.column());
    }

    // If index of selected column is in the list
    if(indexes.contains(index))
    {
        if(indexes.count() > 1)
        {
            // [TODO ?]
        }
    }
    else
    {
        mTableView->selectColumn(index);
    }

    showContextMenuColumn(QCursor::pos());
}
