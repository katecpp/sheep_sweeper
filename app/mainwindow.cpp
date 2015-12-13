#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSettings>
#include <QDebug>
#include <CTopWidget.h>
#include <Constants.h>
#include <CSettingsDialog.h>
#include <CActiveDelegate.h>

namespace SSw
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_model(nullptr),
    m_timer(),
    m_prefs(),
    m_activeDelegate(),
    m_inactiveDelegate()
{
    ui->setupUi(this);

    loadSettings();

    initTable();
    initMenubar();
    initStatusBar();
    initTimer();
    initConnections();

    setWindowIcon(QIcon(QPixmap(BIG_SHEEP_PATH)));
    setWindowTitle(APP);
    newGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    event->accept();
}

void MainWindow::initTable()
{
    m_model = new CTableModel(m_prefs.height, m_prefs.width, m_prefs.sheep, this);
    ui->m_view->setModel(m_model);
    ui->m_view->setItemDelegate(&m_activeDelegate);
}

void MainWindow::initMenubar()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);

    QAction *newGameAction = fileMenu->addAction(tr("&New game"));
    newGameAction->setShortcut(QKeySequence::New);

    QAction *preferencesAction = fileMenu->addAction(tr("&Preferences"));
    preferencesAction->setShortcut(QKeySequence::Preferences);
    //TODO: set another shortkut

    QAction *quitAction = fileMenu->addAction(tr("E&xit"));
    quitAction->setShortcut(QKeySequence::Quit);

    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    QAction *aboutAction = helpMenu->addAction(tr("&About"));

    menuBar()->addMenu(fileMenu);
    menuBar()->addSeparator();
    menuBar()->addMenu(helpMenu);

    connect(newGameAction, SIGNAL(triggered()), this, SLOT(newGame()));
    connect(preferencesAction, SIGNAL(triggered(bool)), this, SLOT(showPreferences()));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutBox()));
}

void  MainWindow::initStatusBar()
{
    statusBar()->showMessage(tr("Sheep is looking at you..."), MSG_TIMEOUT);
}

void MainWindow::initTimer()
{
    m_timer.setInterval(1000);
    connect(m_model, SIGNAL(gameStarted()), &m_timer, SLOT(start())); // TODO: to Qt5
}

void MainWindow::initConnections()
{
    connect(ui->m_view, &CTableView::clicked,       m_model, &CTableModel::onTableClicked);
    connect(ui->m_view, &CTableView::rightClicked,  m_model, &CTableModel::onRightClicked);
    connect(ui->m_view, &CTableView::bothClicked,   m_model, &CTableModel::onBothClicked);

    connect(&m_timer, &QTimer::timeout, this->ui->topWidget, &CTopWidget::incrementTimer);
    connect(m_model, &CTableModel::sheepRemainedDisplay, ui->topWidget, &CTopWidget::setSheepRemainedDisplay);
    //TODO: pressed event

    connect(m_model, &CTableModel::gameLost,        this, &MainWindow::onGameLost);
    connect(m_model, &CTableModel::gameWon,         this, &MainWindow::onGameWon);

    connect(ui->topWidget, &CTopWidget::buttonClicked, this, &MainWindow::newGame);
}

void MainWindow::newGame()
{
    m_timer.stop();

    m_model->newGame(m_prefs.height, m_prefs.width, m_prefs.sheep);
    ui->m_view->reset();
    ui->m_view->setModel(m_model);
    ui->m_view->setEnabled(true);
    ui->m_view->setItemDelegate(&m_activeDelegate);
    ui->topWidget->resetTimer();
    statusBar()->showMessage(tr("Good luck!"), MSG_TIMEOUT);
    updateView();
}

void MainWindow::onGameLost()
{
    m_timer.stop();
    statusBar()->showMessage(tr("Unfortunately, you died."), MSG_TIMEOUT);
    ui->m_view->setItemDelegate(&m_inactiveDelegate);
    ui->m_view->setDisabled(true);
}

void MainWindow::onGameWon()
{
    m_timer.stop();
    statusBar()->showMessage(tr("You won!"), MSG_TIMEOUT);
    ui->m_view->setItemDelegate(&m_inactiveDelegate);
    ui->m_view->setDisabled(true);
}

void MainWindow::showPreferences()
{
    if (CSettingsDialog::getPreferences(m_prefs, this))
    {
        newGame();
    }
}

void MainWindow::showAboutBox()
{
    //TODO: credit for icon
    QMessageBox::about(this, APP, tr("Try to avoid the furious sheep."));
}

void MainWindow::updateView()
{
    ui->m_view->adjustSizeToContents();
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void MainWindow::loadSettings()
{
    QSettings settings;
    m_prefs.width = settings.value("height", int32_t(DEFAULT_HEIGHT)).toInt();
    m_prefs.height  = settings.value("width", int32_t(DEFAULT_WIDTH)).toInt();
    m_prefs.sheep  = settings.value("sheep", int32_t(DEFAULT_SHEEP)).toInt();
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("height", m_prefs.width);
    settings.setValue("width", m_prefs.height);
    settings.setValue("sheep", m_prefs.sheep);
}

} // namespace SSw

