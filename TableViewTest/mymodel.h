#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QList>

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyModel(QObject *parent = 0);
    ~MyModel();
    
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public:
    void loadData(int cols, int rows);

private:
    QVector< double > dataset;
    int cols;
    int rows;
signals:
    
public slots:
    
};



#endif // MYMODEL_H
