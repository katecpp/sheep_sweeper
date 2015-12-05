#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <CTableModel.h>
#include <CTableView.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
    void initStatusBar();
    void initTimer();

    Ui::MainWindow*     ui;
    CTableModel*        m_model;
    QTimer*             m_timer;
};

#endif // MAINWINDOW_H
