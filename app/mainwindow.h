#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <CTableModel.h>
#include <CTableView.h>
#include <SPreferences.h>
#include <CActiveDelegate.h>
#include <CInactiveDelegate.h>

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

public slots:
    void newGame();
    void showAboutBox();
    void showPreferences();
    void updateView();
    void onGameLost();
    void onGameWon();

private:
    void initTable();
    void initMenubar();
    void initConnections();
    void initTimer();
    void loadSettings();
    void saveSettings();

    Ui::MainWindow*     ui;
    CTableModel         m_model;
    QTimer              m_timer;
    SPreferences        m_prefs;
    CActiveDelegate     m_activeDelegate;
    CInactiveDelegate   m_inactiveDelegate;
};

} // namespace SSw

#endif // MAINWINDOW_H
