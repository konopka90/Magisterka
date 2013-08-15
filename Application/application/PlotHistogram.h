#ifndef PLOTHISTOGRAM_H
#define PLOTHISTOGRAM_H

#include "Plot.h"
#include "Table.h"

#include <algorithm>
#include <vector>
#include <qwt_plot_histogram.h>
#include <qwt_samples.h>

class PlotHistogram : public Plot
{
    Q_OBJECT

public:
    PlotHistogram(QWidget * parent);

    void setData(const Table & table, int col);

private:
    void findRanges(double min, double max, int bins, QVector<double>& result);

private:

    QwtPlotHistogram * mHistogram;
    QVector<QwtIntervalSample> mHistogramSamples;

};

#endif // PLOTHISTOGRAM_H
