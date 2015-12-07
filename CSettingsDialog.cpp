#include <CSettingsDialog.h>
#include <ui_CSettingsDialog.h>
#include <Constants.h>
#include <QDebug>

CSettingsDialog::CSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSettingsDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CSettingsDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &CSettingsDialog::reject);
    connect(ui->heightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateRange()));
    connect(ui->widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateRange()));
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
        qDebug() << "Height: " << dialog.ui->heightSpinBox->value();
        qDebug() << "Width: " << dialog.ui->widthSpinBox->value();
        qDebug() << "Sheep: " << dialog.ui->sheepSpinBox->value();
    }
    else
    {
        qDebug() << "Rejected";
    }
}

void CSettingsDialog::updateRange()
{
    qDebug() << "Update ranges";
    int32_t size = ui->heightSpinBox->value() * ui->widthSpinBox->value();
    ui->sheepSpinBox->setRange(MIN_DENSITY * size, MAX_DENSITY * size);
}
