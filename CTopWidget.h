#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include <QWidget>

namespace Ui {
class CTopWidget;
}

class CTopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CTopWidget(QWidget *parent = 0);
    ~CTopWidget();

public slots:
    void incrementTimer();
    void resetTimer();

private:
    Ui::CTopWidget *ui;
    int32_t        m_time;
};

#endif // TOPWIDGET_H
