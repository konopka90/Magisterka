#include "TableModel.h"
#include <exception>
#include <cmath>
#include <QPoint>

using namespace std;

TableModel::TableModel(QObject *parent, int rows, int cols) :
    QAbstractTableModel(parent),
    mRows(rows),
    mCols(cols),
    mData(0),
    mTextFormat('g'),
    mPrecision(12)

{
    // Create columns & fill

    mColumnsVector.resize(mCols);

    for(int i = 0 ; i < mCols ; ++i)
    {
        mColumnsVector[i] = new TableColumn(mRows);

        if(i == 0)
        {
            mColumnsVector[i]->setType(TableColumn::X);
        }
    }

}

TableModel::~TableModel()
{
    if(mData != 0)
    {
        delete [] mData;
    }

    int size = mColumnsVector.size();
    for(int i = 0 ; i < size ; ++i)
    {
        delete mColumnsVector[i];
    }
}


int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mRows;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mCols;
}

int TableModel::rowCount() const
{
    return mRows;
}

int TableModel::columnCount() const
{
    return mCols;
}

int TableModel::validRowCount(const QModelIndexList &columns) const
{
    int minimumIndex = mRows - 1;
    foreach(QModelIndex index, columns)
    {
        QVector<double> vec = mColumnsVector[index.column()]->data();
        for(int i = 0; i < mRows ; ++i)
        {
            if(isnan(vec[i]))
            {
                if(i - 1 < minimumIndex)
                {
                    minimumIndex = i - 1;
                }

                break;
            }
        }
    }

    return minimumIndex + 1;
}


int TableModel::validRowCount(const QVector<int>& columnIndexes) const
{
    int minimumIndex = mRows - 1;
    int size = columnIndexes.size();
    for(int i = 0 ; i < size ; ++i)
    {
        QVector<double> vec = mColumnsVector[columnIndexes[i]]->data();
        for(int i = 0; i < mRows ; ++i)
        {
            if(isnan(vec[i]))
            {
                if(i - 1 < minimumIndex)
                {
                    minimumIndex = i - 1;
                }

                break;
            }
        }
    }

    return minimumIndex + 1;
}

int TableModel::validRowCount(int column) const
{
    QVector<int> columnIndexes;
    columnIndexes.push_back(column);
    return validRowCount(columnIndexes);
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    // double val = mData[index.row()*mCols + index.column()];
    double val = (*mColumnsVector[index.column()])[index.row()];

    if(isnan(val))
    {
        return QVariant();
    }

    if(role == Qt::DisplayRole)
    {
        return QVariant(mLocale.toString(val, mTextFormat, mPrecision));
    }

    if(role == Qt::EditRole)
    {
        QString str = mLocale.toString(val, 'g', mPrecision);
        str = str.replace(" ", "", Qt::CaseInsensitive);
        return QVariant(str);
    }

    return QVariant();
}


Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }
    else
    {
        return Qt::ItemIsEnabled;
    }
}

void TableModel::setValue(int row, int col, double value)
{
    //int pos = row*mCols + col;
    //mData[pos] = value;

    (*mColumnsVector[col]).setValue(row,value);
}

const QVector<TableColumn*>& TableModel::columns() const
{
    return mColumnsVector;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);
    if(!index.isValid())
    {
        return false;
    }

    if(!value.isValid())
    {
        return false;
    }

    //int pos = index.row()*mCols + index.column();

    QString strVal = value.toString();
    if(strVal.isEmpty())
    {
        setValue(index.row(),index.column(),NAN);
        //mData[pos] = NAN;
        return false;
    }

    bool ok = false;
    double val = value.toDouble(&ok);

    if(ok)
    {
        // mData[pos] = val;
        setValue(index.row(),index.column(),val);
    }

    return false;
}


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        QString headerLabel = "";
        switch( mColumnsVector[section]->type() )
        {
        case TableColumn::X:
            headerLabel = "X";
            break;
        case TableColumn::Y:
            headerLabel = "Y";
            break;
        }

        return QVariant( QString::number(section + 1) + " - [" + headerLabel + "]");
    }

    return QAbstractTableModel::headerData(section,orientation,role);
}
