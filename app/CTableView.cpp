#include <CTableView.h>
#include <CActiveDelegate.h>
#include <QHeaderView>

namespace SSw
{

CTableView::CTableView(QWidget *parent)
    : QTableView(parent)
{
    setShowGrid(false);
    horizontalHeader()->hide();
    verticalHeader()->hide();
    horizontalHeader()->setMinimumSectionSize(1);
    verticalHeader()->setMinimumSectionSize(1);
    setSelectionMode(QAbstractItemView::NoSelection);
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

void CTableView::adjustSizeToContents()
{
    resizeColumnsToContents();
    resizeRowsToContents();
    int32_t h = rowHeight(1) * model()->rowCount() + 2;
    int32_t w = columnWidth(1) * model()->columnCount() + 2;
    setFixedSize(w, h);
}

} // namespace SSw
