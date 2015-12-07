#include "CSettingsDialog.h"
#include "ui_CSettingsDialog.h"

CSettingsDialog::CSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSettingsDialog)
{
    ui->setupUi(this);
}

CSettingsDialog::~CSettingsDialog()
{
    delete ui;
}
