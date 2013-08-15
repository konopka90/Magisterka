#ifndef TABLEVIEWMODEL_H
#define TABLEVIEWMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QLocale>

#include "TableColumn.h"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = 0, int rows = DEFAULT_ROWS , int cols = DEFAULT_COLS);
    ~TableModel();
    
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    // Returns number of rows
    int rowCount() const;
    int columnCount() const;

    // Returns number of valid rows for given columns
    int validRowCount(const QModelIndexList &columns) const;
    int validRowCount(const QVector<int>& columnIndexes) const;
    int validRowCount(int column) const;


    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void setValue(int row, int col, double value);

    // Getter for vector of columns with data.
    const QVector<TableColumn*>& columns() const;

private:

    static const int DEFAULT_ROWS = 20;
    static const int DEFAULT_COLS = 3;

private:
    int mRows;
    int mCols;
    double * mData;
    QVector<TableColumn*> mColumnsVector;


    QLocale mLocale;
    char mTextFormat;
    int mPrecision;

signals:
    
public slots:



    // QAbstractItemModel interface
public:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // TABLEVIEWMODEL_H
