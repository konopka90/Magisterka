#include "PlotDialog.h"
#include <QMessageBox>
PlotDialog::PlotDialog(QWidget *parent) :
    QDialog(parent),
    mResult(Cancel)
{
    mVLayout = new QVBoxLayout();
    mHLayout = new QHBoxLayout();
    mButtonCancel = new QPushButton("Cancel");
    mButtonOnOnePlot = new QPushButton("On one plot");
    mButtonOnSeparatePlots = new QPushButton("On separate plots");
    mLabel = new QLabel("What do you want to do?");

    mButtonOnOnePlot->setDefault(true);

    mHLayout->addWidget(mButtonOnOnePlot);
    mHLayout->addWidget(mButtonOnSeparatePlots);
    mHLayout->addWidget(mButtonCancel);

    mVLayout->addWidget(mLabel,10);
    mVLayout->addLayout(mHLayout);

    mVLayout->setAlignment(mHLayout,Qt::AlignCenter);
    mVLayout->setAlignment(mLabel,Qt::AlignCenter);

    connect(mButtonOnOnePlot, SIGNAL(clicked()),this,SLOT(onOnePlotClicked()));
    connect(mButtonOnSeparatePlots, SIGNAL(clicked()),this,SLOT(onSeparatePlotClicked()));
    connect(mButtonCancel, SIGNAL(clicked()),this,SLOT(onCancelClicked()));

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setLayout(mVLayout);
    this->adjustSize();
    this->setFixedSize(this->size());
}

PlotDialog::Result PlotDialog::result() const
{
    return mResult;
}

void PlotDialog::onOnePlotClicked()
{
    mResult = OnePlot;
    this->close();
}

void PlotDialog::onSeparatePlotClicked()
{
    mResult = SeparatePlots;
    this->close();
}

void PlotDialog::onCancelClicked()
{
    mResult = Cancel;
    this->close();
}

