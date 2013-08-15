#include "Plot.h"

Plot::Plot(QWidget *parent) :
    Window(parent)
{
    mColors[0] = QColor("blue");
    mColors[1] = QColor("red");
    mColors[2] = QColor("green");

    mPlot.setMinimumWidth(1);
    mPlot.setMinimumHeight(1);
    mPlot.setTitle("Plot");
    mPlot.setAxisTitle(QwtPlot::xBottom, "X Axis");
    mPlot.setAxisTitle(QwtPlot::yLeft, "Y Axis");

    setWidget(&mPlot);

}

QColor Plot::getPenColor(int colorNumber)
{
    if(colorNumber < MAXIMUM_PLOTS_ON_ONE_CANVAS)
    {
        return mColors[colorNumber];
    }

    return QColor("black");
}
