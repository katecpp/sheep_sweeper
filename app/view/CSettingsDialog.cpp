#include <view/CSettingsDialog.h>
#include <ui_CSettingsDialog.h>
#include <Constants.h>

namespace SSw
{

CSettingsDialog::CSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSettingsDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CSettingsDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &CSettingsDialog::reject);
    connect(ui->heightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateRange()));
    connect(ui->widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateRange()));

    ui->heightSpinBox->setMinimum(3);
    ui->widthSpinBox->setMinimum(3);

    setWindowTitle(tr("Preferences"));
}

CSettingsDialog::~CSettingsDialog()
{
    delete ui;
}

bool CSettingsDialog::getPreferences(SPreferences &prefs, QWidget *parent)
{
    bool retValue = false;

    CSettingsDialog dialog(parent);

    dialog.ui->heightSpinBox->setValue(prefs.width);
    dialog.ui->widthSpinBox->setValue(prefs.height);
    dialog.ui->sheepSpinBox->setValue(prefs.sheep);

    if (dialog.exec() == QDialog::Accepted)
    {
        prefs.width   = dialog.ui->heightSpinBox->value();
        prefs.height  = dialog.ui->widthSpinBox->value();
        prefs.sheep   = dialog.ui->sheepSpinBox->value();
        retValue = true;
    }

    return retValue;
}

void CSettingsDialog::updateRange()
{
    int32_t min = MIN_DENSITY * ui->heightSpinBox->value() * ui->widthSpinBox->value();
    int32_t max = MAX_DENSITY * ui->heightSpinBox->value() * ui->widthSpinBox->value();
    ui->sheepSpinBox->setRange(min, max);
}

} // namespace SSw
