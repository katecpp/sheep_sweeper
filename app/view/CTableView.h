#ifndef CTABLEVIEW_H
#define CTABLEVIEW_H

#include <QTableView>
#include <QMouseEvent>
#include <view/CActiveDelegate.h>
#include <view/CInactiveDelegate.h>

namespace SSw
{

class CTableView : public QTableView
{
    Q_OBJECT
public:
    CTableView(QWidget *parent = 0);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void adjustSizeToContents();

public slots:
    void activate();
    void deactivate();

signals:
    void rightClicked(const QModelIndex& index);
    void bothClicked(const QModelIndex& index);

private:
    CActiveDelegate     m_activeDelegate;
    CInactiveDelegate   m_inactiveDelegate;
};

} // namespace SSw

#endif // CTABLEVIEW_H
