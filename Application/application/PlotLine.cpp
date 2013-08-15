#include "PlotLine.h"

PlotLine::PlotLine(QWidget *parent)
    : Plot(parent)
{
    // mCurve.setTitle("Title");
    // mCurve.setPen(Qt::blue, 2);

    mLegend.setWhatsThis("Legenda");
    mLegend.resize(100,30);
    mPlot.insertLegend(&mLegend, QwtPlot::RightLegend, 10);
}

PlotLine::~PlotLine()
{
    int size = mCurveVector.size();
    for(int i = 0 ; i < size ; ++i)
    {
        delete mCurveVector[i];
    }
}

void PlotLine::addCurve(const Table & table, int colX, int colY) throw(ErrorException)
{
    uint curveVectorSize = (uint)mCurveVector.size();

    if(curveVectorSize >= MAXIMUM_PLOTS_ON_ONE_CANVAS)
    {
        throw ErrorException("Maximum curves reached.");
    }

    // Get columns

    const TableModel & model = table.model();
    const QVector<TableColumn *> & columns = model.columns();

    TableColumn * xColumn = columns[colX];
    const QVector<double>& xDataVec = xColumn->data();

    TableColumn * yColumn = columns[colY];
    const QVector<double>& yDataVec = yColumn->data();

    if(xDataVec.size() < 1 || yDataVec.size() < 1 )
    {
        throw ErrorException("Data is empty.");
    }

    // Get values

    const double * xData = &xDataVec[0];
    const double * yData = &yDataVec[0];

    QVector<int> selectedColumns;
    selectedColumns.push_back(colX);
    selectedColumns.push_back(colY);
    int size = model.validRowCount(selectedColumns);

    // Setup curve

    QwtPlotCurve * curve = new QwtPlotCurve();
    curve->setSamples(xData,yData,size);

    QColor color = this->getPenColor(curveVectorSize);
    curve->setPen(color, DEFAULT_PEN_SIZE);

    curve->setTitle(QString::number(curveVectorSize + 1));

    curve->attach( &mPlot );
    mCurveVector.push_back(curve);
}
