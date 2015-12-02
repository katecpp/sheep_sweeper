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
    void updateView();

private:
    static const char* APP_NAME() { return "Sheep sweeper 0.1"; }

    void initTable();
    void initMenubar();
    void initConnections();

    Ui::MainWindow*     ui;
    CTableModel*        m_model;
    CTableView*         m_view;
};

#endif // MAINWINDOW_H
