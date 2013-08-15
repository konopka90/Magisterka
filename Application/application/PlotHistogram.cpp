#include "PlotHistogram.h"

using namespace std;

PlotHistogram::PlotHistogram(QWidget * parent)
    : Plot(parent)
{
    mHistogram = new QwtPlotHistogram();
    mHistogram->attach(&mPlot);
    mHistogram->setBrush(QBrush(QColor(0, 50, 0, 25)));

    mPlot.setTitle("Histogram");
}

void PlotHistogram::setData(const Table & table, int col)
{
    const TableModel & m = table.model();
    TableColumn * column = m.columns().at(col);



    // Get minimum & maximum

    double min = column->min();
    double max = column->max();

    // Get valid rows
    int rowsCount = m.validRowCount(col);

    // Struges formula
    // int bins = ceil(log2(rowsCount) + 1);

    // Sqare-root choice
    int bins = sqrt(rowsCount);

    // Find ranges

    QVector<double> ranges;
    findRanges(min,max,bins,ranges);

    // Make histogram

    int position = 0;
    double comparedValue = 0.0;

    QVector<int> histogramValues(bins);

    for(int i = 0 ; i < rowsCount ; ++i)
    {
        comparedValue = (*column)[i];

        // Find position in histogram

        position = 0;
        for(int j = 0 ; j < bins ; ++j)
        {
            if( comparedValue <= ranges[j + 1] )
            {
                break;
            }
            else
            {
                position++;
            }
        }

        histogramValues[position]++;
    }

    // Prepare bins

    mHistogramSamples.clear();
    for(int i = 0 ; i < bins ; ++i)
    {
        mHistogramSamples.push_back(QwtIntervalSample(histogramValues[i],ranges[i],ranges[i+1]));
    }


    // Set histogram data

    mHistogram->setSamples(mHistogramSamples);

}

void PlotHistogram::findRanges(double min, double max, int bins, QVector<double>& result)
{
    // First is minimum
    result.push_back(min);

    double interval = (max - min)/(double)bins;

    for(int i = 0 ; i < bins - 1 ; ++i)
    {
        result.push_back(min + interval*(i+1));
    }

    // Last is maximum

    result.push_back(max);
}
