#ifndef CTABLEVIEW_H
#define CTABLEVIEW_H

#include <QObject>
#include <QTableView>

class CTableView : public QTableView
{
    Q_OBJECT
public:
    CTableView(QWidget *parent = 0);
    // TODO: mouse events capture
};

#endif // CTABLEVIEW_H
