#include "TableColumn.h"

using namespace std;


TableColumn::TableColumn(int rows)
    : mType(Y)
{
    mData.resize(rows);
    for(int i = 0 ; i < rows ; ++i)
    {
        mData[i] = NAN;
    }
}

void TableColumn::setValue(int row, double value)
{
    mData[row] = value;
}

void TableColumn::setType(TableColumn::ColumnType type)
{
    mType = type;
}

TableColumn::ColumnType TableColumn::type() const
{
    return mType;
}

double TableColumn::operator[](int row) const
{
    return mData[row];
}

const ValuesContainer& TableColumn::data() const
{
    return mData;
}

double TableColumn::min() const
{
    Q_ASSERT(mData.size() > 0);
    double result = std::numeric_limits<double>::max();
    foreach(double d, mData)
    {
        if(!isnan(d))
        {
            result = qMin(result,d);
        }
    }

    return result;
}

double TableColumn::max() const
{
    Q_ASSERT(mData.size() > 0);
    double result = std::numeric_limits<double>::min();
    foreach(double d, mData)
    {
        if(!isnan(d))
        {
            result = qMax(result,d);
        }
    }

    return result;
}
