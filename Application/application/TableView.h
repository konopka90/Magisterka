#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QMouseEvent>
#include <QTableView>
#include <QHeaderView>

class TableView : public QTableView
{
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = 0);
    
signals:
    
public slots:
    

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // TABLEVIEW_H
