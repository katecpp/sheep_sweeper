#ifndef CSETTINGSDIALOG_H
#define CSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class CSettingsDialog;
}

class CSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CSettingsDialog(QWidget *parent = 0);
    ~CSettingsDialog();

private:
    Ui::CSettingsDialog *ui;
};

#endif // CSETTINGSDIALOG_H
