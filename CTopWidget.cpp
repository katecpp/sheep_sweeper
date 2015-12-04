#include "CTopWidget.h"
#include "ui_CTopWidget.h"

CTopWidget::CTopWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CTopWidget),
    m_time(0)
{
    ui->setupUi(this);
    //TODO: setDigitCount

    QIcon buttonIcon(QPixmap(":/images/images/small_sheep.png"));
    ui->pushButton->setIcon(buttonIcon);
    //ui->pushButton->setIconSize(buttonIcon.size());
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

}
