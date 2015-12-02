#include <CTableView.h>
#include <QDebug>

CTableView::CTableView(QWidget *parent)
    : QTableView(parent)
{
}

void CTableView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        QModelIndex index = indexAt(event->pos());
        emit rightClicked(index);
    }
    else
    {
        QTableView::mouseReleaseEvent(event);
    }
}
