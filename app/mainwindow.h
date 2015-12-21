#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTranslator>
#include <CTableModel.h>
#include <CTableView.h>
#include <SPreferences.h>

namespace Ui {
class MainWindow;
}

namespace SSw
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

public slots:
    void newGame();
    void onGameLost();
    void onGameWon();
    void showAboutBox();
    void showPreferences();
    void updateView();

private:
    void initTable();
    void initMenubar();
    void initConnections();
    void initTimer();
    void loadSettings();
    void saveSettings();
    void setLanguage();

    Ui::MainWindow*     ui;
    CTableModel         m_model;
    QTimer              m_timer;
    SPreferences        m_prefs;
    QTranslator         m_translator;
};

} // namespace SSw

#endif // MAINWINDOW_H
