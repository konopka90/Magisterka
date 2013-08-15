#include "TableView.h"

TableView::TableView(QWidget *parent) :
    QTableView(parent)
{
}


void TableView::mousePressEvent(QMouseEvent * event)
{
    QTableView::mousePressEvent(event);

    if(event->button() == Qt::RightButton)
    {
        int index = this->columnAt(event->pos().x());
    }

}

void TableView::mouseReleaseEvent(QMouseEvent * event)
{
    QTableView::mouseReleaseEvent(event);
}
