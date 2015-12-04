#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <CFieldDelegate.h>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QDebug>
#include <CTopWidget.h>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_model(nullptr),
    m_timer(nullptr)
{
    ui->setupUi(this);

    initTable();
    initConnections();
    initMenubar();
    initStatusBar();
    initTimer();

    setWindowIcon(QIcon(QPixmap(":/images/images/big_sheep.png")));
    setWindowTitle(tr(APP_NAME()));
    //resize(340, 360);
    // FIXME: set proper window size
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTable()
{
    m_model = new CTableModel(10, 10, 10, this);

    ui->m_view->setShowGrid(false);
    ui->m_view->horizontalHeader()->hide();
    ui->m_view->verticalHeader()->hide();
    ui->m_view->horizontalHeader()->setMinimumSectionSize(1);
    ui->m_view->verticalHeader()->setMinimumSectionSize(1);
    ui->m_view->setModel(m_model);
    ui->m_view->setSelectionMode(QAbstractItemView::NoSelection);
    //ui->m_view->resize(250,250);

    CFieldDelegate *delegate = new CFieldDelegate(this);
    ui->m_view->setItemDelegate(delegate);
}

void MainWindow::initMenubar()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);

    QAction *newGameAction = fileMenu->addAction(tr("&New game"));
    newGameAction->setShortcut(QKeySequence::New);

    QAction *quitAction = fileMenu->addAction(tr("E&xit"));
    quitAction->setShortcut(QKeySequence::Quit);

    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    QAction *aboutAction = helpMenu->addAction(tr("&About"));

    menuBar()->addMenu(fileMenu);
    menuBar()->addSeparator();
    menuBar()->addMenu(helpMenu);

    connect(newGameAction, SIGNAL(triggered()), this, SLOT(newGame()));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutBox()));
}

void  MainWindow::initStatusBar()
{
    statusBar()->showMessage(tr("Sheep are looking at you..."), 5000);
}

void MainWindow::initTimer()
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this->ui->topWidget, &CTopWidget::incrementTimer);
    connect(m_model, &CTableModel::gameLost,    m_timer, &QTimer::stop);
    connect(m_model, &CTableModel::gameWon,     m_timer, &QTimer::stop);
}

void MainWindow::initConnections()
{
    connect(ui->m_view, &CTableView::clicked,       m_model, &CTableModel::onTableClicked);
    connect(ui->m_view, &CTableView::rightClicked,  m_model, &CTableModel::onRightClicked);

    connect(m_model, &CTableModel::gameLost,    this,   &MainWindow::onGameLost);
    connect(m_model, &CTableModel::gameWon,     this,   &MainWindow::onGameWon);

    //TODO: pressed event
}

void MainWindow::newGame()
{
    m_model->newGame();
    ui->m_view->reset();
    ui->m_view->setEnabled(true);
    m_timer->start();
}

void MainWindow::onGameLost()
{
    ui->m_view->setDisabled(true);
    statusBar()->showMessage(tr("Unfortunately, you died."), 5000);
}

void MainWindow::onGameWon()
{
    statusBar()->showMessage(tr("You won!"), 5000);
}

void MainWindow::showAboutBox()
{
    //TODO: credit for icon
    QMessageBox::about(this, tr(APP_NAME()),
        tr("Try to avoid the furious sheep."));
}

void MainWindow::updateView()
{
    ui->m_view->resizeColumnsToContents();
    ui->m_view->resizeRowsToContents();
}
