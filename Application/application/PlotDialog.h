#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class PlotDialog : public QDialog
{
    Q_OBJECT
public:

    enum Result
    {
        OnePlot,
        SeparatePlots,
        Cancel
    };

    explicit PlotDialog(QWidget *parent = 0);
    Result result() const;

private:

    QVBoxLayout * mVLayout;
    QHBoxLayout * mHLayout;

    QLabel * mLabel;
    QPushButton * mButtonOnOnePlot;
    QPushButton * mButtonOnSeparatePlots;
    QPushButton * mButtonCancel;

    Result mResult;

signals:
    
public slots:

    void onOnePlotClicked();
    void onSeparatePlotClicked();
    void onCancelClicked();


};

#endif // PLOTDIALOG_H
