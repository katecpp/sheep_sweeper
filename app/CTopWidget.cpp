#include "CTopWidget.h"
#include "ui_CTopWidget.h"
#include <Constants.h>
#include <QPixmap>

namespace SSw
{

CTopWidget::CTopWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CTopWidget),
    m_time(0),
    m_normalFace(QPixmap(NORMAL_FACE)),
    m_fearFace(QPixmap(FEAR_FACE)),
    m_happyFace(QPixmap(HAPPY_FACE)),
    m_sadFace(QPixmap(SAD_FACE))
{
    ui->setupUi(this);
    init();
    //TODO: setDigitCount
}

CTopWidget::~CTopWidget()
{
    delete ui;
}

void CTopWidget::incrementTimer()
{
    m_time++;
    ui->lcdTime->display(m_time);
}

void CTopWidget::resetTimer()
{
    m_time = 0;
    ui->lcdTime->display(m_time);
}

void CTopWidget::setSheepRemainedDisplay(int32_t sheepRemained)
{
    ui->lcdSheep->display(sheepRemained);
}

void CTopWidget::setPressed(bool pressed)
{
    if (pressed)
    {
        ui->pushButton->setIcon(m_fearFace);
    }
    else
    {
        ui->pushButton->setIcon(m_normalFace);
    }
}

void CTopWidget::setVictory(bool victory)
{
    if (victory)
    {
        ui->pushButton->setIcon(m_happyFace);
    }
    else
    {
        ui->pushButton->setIcon(m_sadFace);
    }
}

void CTopWidget::setDefault()
{
    ui->pushButton->setIcon(m_normalFace);
}

void CTopWidget::init()
{
    setDefault();
    ui->pushButton->setIconSize(QSize(30,30));

    connect(ui->pushButton, &QPushButton::clicked, this, &CTopWidget::buttonClicked);
}

} // namespace SSw
