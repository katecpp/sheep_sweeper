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
    virtual QSize sizeHint() const;

signals:
    void buttonClicked();

public slots:
    void setSheepRemainedDisplay(int32_t sheepRemained);
    void incrementTimer();
    void resetTimer();

private:
    void init();

    Ui::CTopWidget *ui;
    int32_t        m_time;
};

#endif // TOPWIDGET_H
