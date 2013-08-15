#ifndef PLOT_H
#define PLOT_H

#include <QMessageBox>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>

#include "Table.h"
#include "Window.h"
#include "Exceptions.h"

class Plot : public Window
{
    Q_OBJECT
public:
    explicit Plot(QWidget *parent = 0);
    virtual ~Plot() {}

    static const unsigned int MAXIMUM_PLOTS_ON_ONE_CANVAS = 3;
    static const unsigned int DEFAULT_PEN_SIZE = 1;

protected:
    QColor getPenColor(int colorNumber);

protected:
    QwtPlot mPlot;
    QwtLegend mLegend;

private:
    QColor mColors[MAXIMUM_PLOTS_ON_ONE_CANVAS];

signals:
    
public slots:
    
};

#endif // PLOT_H
