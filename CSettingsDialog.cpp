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

    ui->heightSpinBox->setMinimum(2);
    ui->widthSpinBox->setMinimum(2);
}

CSettingsDialog::~CSettingsDialog()
{
    delete ui;
}

bool CSettingsDialog::getPreferences(int32_t &width, int32_t &height, int32_t &sheep, QWidget *parent)
{
    bool retValue = false;

    CSettingsDialog dialog(parent);

    dialog.ui->heightSpinBox->setValue(height);
    dialog.ui->widthSpinBox->setValue(width);
    dialog.ui->sheepSpinBox->setValue(sheep);

    if (dialog.exec() == QDialog::Accepted)
    {
        qDebug() << "Accepted";
        height  = dialog.ui->heightSpinBox->value();
        width   = dialog.ui->widthSpinBox->value();
        sheep   = dialog.ui->sheepSpinBox->value();
        retValue = true;
    }
    else
    {
        qDebug() << "Rejected";
    }

    return retValue;
}

void CSettingsDialog::updateRange()
{
    qDebug() << "Update ranges";
    int32_t size = ui->heightSpinBox->value() * ui->widthSpinBox->value();
    ui->sheepSpinBox->setRange(MIN_DENSITY * size, MAX_DENSITY * size);
}
