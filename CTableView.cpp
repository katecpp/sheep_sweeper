#include <CTableView.h>

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

QSize CTableView::sizeHint() const
{
    QStyleOptionViewItem option;
    QModelIndex index;

    int32_t itemHeight = itemDelegate()->sizeHint(option, index).height() + 1;
    int32_t y = itemHeight * model()->columnCount() + 2;

    int32_t itemWidth = itemDelegate()->sizeHint(option, index).width() + 1;
    int32_t x = itemWidth * model()->rowCount();

    return QSize(x, y);
}
