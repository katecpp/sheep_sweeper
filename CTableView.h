#ifndef CTABLEVIEW_H
#define CTABLEVIEW_H

#include <QTableView>
#include <QMouseEvent>

class CTableView : public QTableView
{
    Q_OBJECT
public:
    CTableView(QWidget *parent = 0);
    virtual void mouseReleaseEvent(QMouseEvent* event);

signals:
    void rightClicked(const QModelIndex& index);
};

#endif // CTABLEVIEW_H
