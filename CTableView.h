#ifndef CTABLEVIEW_H
#define CTABLEVIEW_H

#include <QTableView>
#include <QMouseEvent>

namespace SSw
{

class CTableView : public QTableView
{
    Q_OBJECT
public:
    CTableView(QWidget *parent = 0);
    virtual void mouseReleaseEvent(QMouseEvent* event);

signals:
    void rightClicked(const QModelIndex& index);
    void bothClicked(const QModelIndex& index);
};

} // namespace SSw

#endif // CTABLEVIEW_H
