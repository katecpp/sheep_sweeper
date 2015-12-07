#include <CSettingsDialog.h>
#include <ui_CSettingsDialog.h>
#include <QDebug>

CSettingsDialog::CSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSettingsDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

CSettingsDialog::~CSettingsDialog()
{
    delete ui;
}

void CSettingsDialog::getPreferences(QWidget *parent)
{
    CSettingsDialog dialog(parent);
    if (dialog.exec() == QDialog::Accepted)
    {
        qDebug() << "Accepted";
    }
    else
    {
        qDebug() << "Rejected";
    }
}
