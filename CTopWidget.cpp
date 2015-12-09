#include "CTopWidget.h"
#include "ui_CTopWidget.h"
#include <Constants.h>
#include <QPixmap>
#include <QIcon>
CTopWidget::CTopWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CTopWidget),
    m_time(0)
{
    ui->setupUi(this);
    init();
    //TODO: setDigitCount

    QPixmap smallSheep(SMALL_SHEEP_PATH);
    QIcon buttonIcon(smallSheep);
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
    m_time = 0;
    ui->lcdTime->display(m_time);
}

void CTopWidget::setSheepRemainedDisplay(int32_t sheepRemained)
{
    ui->lcdSheep->display(sheepRemained);
}

void CTopWidget::init()
{
    connect(ui->pushButton, &QPushButton::clicked, this, &CTopWidget::buttonClicked);
}
