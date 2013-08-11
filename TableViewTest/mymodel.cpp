#include "mymodel.h"
#include <QMessageBox>

using namespace std;

MyModel::MyModel(QObject *parent) :
    QAbstractTableModel(parent),
    cols(0),
    rows(0)
{}

MyModel::~MyModel()
{}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
    return rows;
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return cols;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        int pos = index.row()*cols+index.column();
        if(pos < dataset.size())
        {
            return QString("%1")
                    //.arg((*dataset)[index.row()*cols+index.column()]);
                    .arg(dataset.at(index.row()*cols+index.column()));
        }
    }

    return QVariant();
}

void MyModel::loadData(int cols, int rows)
{
    dataset.clear();
    dataset.resize(0);

    try
    {
        dataset.reserve(cols*rows);

        for(int i = 0 ; i < rows ; ++i)
        {
            for(int j = 0 ; j < cols ; ++j)
            {
                dataset.push_back((double)((i*cols+j)));
            }
        }

        this->cols = cols;
        this->rows = rows;

    }
    catch(std::bad_alloc& ba)
    {
        QMessageBox::information(0,tr(""),tr("Brak pamieci."));
        dataset.clear();
        this->cols = 0;
        this->rows = 0;
    }

    this->reset();
}
