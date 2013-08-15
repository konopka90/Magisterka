#ifndef PLOTLINE_H
#define PLOTLINE_H

#include "Plot.h"

#include <QVector>

class PlotLine : public Plot
{
    Q_OBJECT

public:
    PlotLine(QWidget *parent = 0);
    ~PlotLine();

    void addCurve(const Table & table, int colX, int colY) throw(ErrorException);

private:

    QVector<QwtPlotCurve*> mCurveVector;


};

#endif // PLOTLINE_H
