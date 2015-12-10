#include <CTableView.h>
#include <QDebug>

namespace SSw
{

CTableView::CTableView(QWidget *parent)
    : QTableView(parent)
{
}

void CTableView::mouseReleaseEvent(QMouseEvent* event)
{
    QModelIndex index = indexAt(event->pos());

    switch (event->button())
    {
        case Qt::RightButton:
        {
            emit rightClicked(index);
            break;
        }

        case Qt::LeftButton:
        {
            if (event->buttons() & Qt::RightButton)
            {
                emit bothClicked(index);
            }
            else
            {
                QTableView::mouseReleaseEvent(event);
            }

            break;
        }

        default:
        {
            break;
        }
    }
}

} // namespace SSw
