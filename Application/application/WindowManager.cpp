#include "WindowManager.h"

WindowManager & WindowManager::getInstance(QWidget *parent)
{
    static WindowManager manager(parent);
    return manager;
}

WindowManager::WindowManager(QWidget *parent)
{
    mMdiArea = new QMdiArea(parent);
}

inline const Table& WindowManager::getActiveTable() throw(std::bad_cast)
{
    return dynamic_cast<Table&>(*(getArea()->activeSubWindow()));
}


ColumnPairsList WindowManager::getPlotPairs(const Table & table)
{
    // Access selected columns

    const TableModel & model = table.model();

    QVector<TableColumn *> columns = model.columns();
    QItemSelectionModel * select = table.view().selectionModel();
    QModelIndexList list = select->selectedColumns();

    // Sort by selection

    qSort(list.begin(), list.end(),ColumnComparator(table));

    // Make pairs

    ColumnPairsList pairs;

    for(QModelIndexList::const_iterator it = list.constBegin(); it!=list.constEnd() ; ++it)
    {
        int index = (*it).column();

        // Check if column type is X
        if(columns[index]->type() == TableColumn::X)
        {
            // Check if next is Y
            QModelIndexList::const_iterator next = it+1;

            if(next == list.constEnd())
            {
                continue;
            }

            int nextIndex = (*next).column();
            if(columns[nextIndex]->type() != TableColumn::Y)
            {
                continue;
            }

            // Create new pair
            ColumnPair pair;
            pair.columnX = index;

            // Find all Y-cols for current column X
            QModelIndexList::const_iterator sub_it;
            for(sub_it = it + 1; sub_it != list.constEnd() ; ++sub_it)
            {
                nextIndex = (*sub_it).column();
                if(columns[nextIndex]->type() == TableColumn::Y)
                {
                    pair.columnsY.push_back(nextIndex);
                }
                else
                if(columns[nextIndex]->type() == TableColumn::X)
                {
                    break;
                }
            }

            // Insert pair
            if(pair.columnsY.count() > 0)
            {
                pairs.append(pair);
            }
        }
    }

    return pairs;
}

void WindowManager::initTable(Table *table)
{
    // Events
    connect(table,SIGNAL(menuPlotLineClicked()),this,SLOT(plotLine()));
    connect(table,SIGNAL(menuPlotHistogramClicked()),this,SLOT(plotHistogram()));

    // Actions
    table->show();
}

QMdiArea* WindowManager::getArea() const
{
    return mMdiArea;
}

void WindowManager::createEmptyTable()
{
    Table * table = new Table(mMdiArea);
    initTable(table);
}

void WindowManager::createTableFromFile(const QString& filename)
{
    Table * table = new Table(filename, mMdiArea);
    initTable(table);
}

void WindowManager::plotLine()
{
    try
    {
        const Table & table = getActiveTable();

        // Get all available pairs that can be plotted
        ColumnPairsList pairs = getPlotPairs(table);

        if(pairs.count() == 0)
        {
            QMessageBox::critical(0,"Error","Select at least two columns (X and Y).");
            return;
        }

        PlotLine * plotPtr;

        foreach(ColumnPair pair, pairs)
        {
            PlotDialog::Result result = PlotDialog::OnePlot;

            // If there are selected more than 1 Y's , ask user what to do

            if(pair.columnsY.count() > 1)
            {
                PlotDialog dialog(this);
                dialog.exec();
                result = dialog.result();
            }

            switch(result)
            {
            case PlotDialog::OnePlot:

                plotPtr = new PlotLine(mMdiArea);
                for(int i = 0 ; i < pair.columnsY.count() ; ++i)
                {
                    if(!addCurveToPlot(table,plotPtr,pair.columnX,pair.columnsY[i]))
                    {
                        break;
                    }
                }
                plotPtr->show();
                break;

            case PlotDialog::SeparatePlots:

                for(int i = 0 ; i < pair.columnsY.count() ; ++i)
                {
                    plotPtr = new PlotLine(mMdiArea);
                    addCurveToPlot(table,plotPtr,pair.columnX,pair.columnsY[i]);
                    plotPtr->show();
                }


                break;

            case PlotDialog::Cancel:
                    break;
                break;

            }
        }
    }
    catch(std::bad_cast e)
    {
        showNoTableActivatedError();
    }
}

void WindowManager::plotHistogram()
{
    try
    {
        // Get active table

        const Table & table = getActiveTable();

        // Get selected columns

        const TableModel & model = table.model();

        QVector<TableColumn *> columns = model.columns();
        QItemSelectionModel * select = table.view().selectionModel();
        QModelIndexList list = select->selectedColumns();

        if(list.size() == 0)
        {
            QMessageBox::critical(0,"Error","Select column.");
            return;
        }

        // Sort by selection

        qSort(list.begin(), list.end(),ColumnComparator(table));

        // Take first

        QModelIndex index = *(list.begin());

        PlotHistogram * h = new PlotHistogram(mMdiArea);
        h->setData(table,index.column());
        h->show();

    }
    catch(std::bad_cast e)
    {
        showNoTableActivatedError();
    }

}

bool WindowManager::addCurveToPlot(const Table & table, PlotLine * plotLine, int colX, int colY)
{
    try
    {
        plotLine->addCurve(table,colX,colY);
        return true;
    }
    catch(ErrorException& ee)
    {
        QMessageBox::critical(0,"Error",ee.what());
        return false;
    }
}

void WindowManager::showNoTableActivatedError()
{
    QMessageBox::critical(0,"Error","Click on table.");
}
