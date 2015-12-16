#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include <QWidget>
#include <QIcon>

namespace Ui {
class CTopWidget;
}

namespace SSw
{

class CTopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CTopWidget(QWidget *parent = 0);
    ~CTopWidget();

signals:
    void buttonClicked();

public slots:
    void setSheepRemainedDisplay(int32_t sheepRemained);
    void incrementTimer();
    void resetTimer();
    void setPressed(bool pressed);
    void setVictory(bool victory);
    void setDefault();

private:
    void init();

    Ui::CTopWidget *ui;
    int32_t        m_time;
    QIcon          m_normalFace;
    QIcon          m_fearFace;
    QIcon          m_happyFace;
    QIcon          m_sadFace;
};

} // namespace SSw

#endif // TOPWIDGET_H
