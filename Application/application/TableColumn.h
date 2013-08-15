#ifndef TABLECOLUMN_H
#define TABLECOLUMN_H

#include <QVector>
#include <cmath>
#include <limits>
#include <QtAlgorithms>

typedef QVector<double> ValuesContainer;

class TableColumn
{
public:
    enum ColumnType { X, Y };

public:
    TableColumn(int rows);

    void setValue(int row, double value);
    void setType(ColumnType type);
    ColumnType type() const;

    double operator[](int row) const;

    const ValuesContainer& data() const;

    double min() const;
    double max() const;


private:

    ValuesContainer mData;
    ColumnType mType;
};

#endif // TABLECOLUMN_H
