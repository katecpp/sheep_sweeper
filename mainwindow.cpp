#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <CFieldDelegate.h>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSettings>
#include <QDebug>
#include <CTopWidget.h>
#include <QTimer>
#include <Constants.h>
#include <CSettingsDialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_model(nullptr),
    m_timer(nullptr),
    m_height(DEFAULT_HEIGHT),
    m_width(DEFAULT_WIDTH),
    m_sheep(DEFAULT_SHEEP)
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
    m_model = new CTableModel(m_width, m_height, m_sheep, this);

    CFieldDelegate *delegate = new CFieldDelegate(this);
    ui->m_view->setItemDelegate(delegate);
    ui->m_view->setShowGrid(false);
    ui->m_view->horizontalHeader()->hide();
    ui->m_view->verticalHeader()->hide();
    ui->m_view->horizontalHeader()->setMinimumSectionSize(1);
    ui->m_view->verticalHeader()->setMinimumSectionSize(1);
    ui->m_view->setModel(m_model);
    ui->m_view->setSelectionMode(QAbstractItemView::NoSelection);
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
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_model, SIGNAL(gameStarted()), m_timer, SLOT(start())); // TODO: to Qt5
    connect(m_model, &CTableModel::gameLost,    m_timer, &QTimer::stop);
    connect(m_model, &CTableModel::gameWon,     m_timer, &QTimer::stop);
}

void MainWindow::initConnections()
{
    connect(ui->m_view, &CTableView::clicked,       m_model, &CTableModel::onTableClicked);
    connect(ui->m_view, &CTableView::rightClicked,  m_model, &CTableModel::onRightClicked);

    connect(m_model, &CTableModel::gameLost,    this,   &MainWindow::onGameLost);
    connect(m_model, &CTableModel::gameWon,     this,   &MainWindow::onGameWon);

    connect(m_timer, &QTimer::timeout, this->ui->topWidget, &CTopWidget::incrementTimer);
    connect(m_model, &CTableModel::sheepRemainedDisplay, ui->topWidget, &CTopWidget::setSheepRemainedDisplay);
    //TODO: pressed event

    connect(ui->topWidget, &CTopWidget::buttonClicked, this, &MainWindow::newGame);
}

void MainWindow::newGame()
{
    if (m_timer->isActive())
    {
        m_timer->stop();
    }

    m_model->newGame(m_width, m_height, m_sheep);
    ui->m_view->reset();
    ui->m_view->setModel(m_model);
    ui->m_view->setEnabled(true);
    ui->topWidget->resetTimer();
    statusBar()->showMessage(tr("Good luck!"), MSG_TIMEOUT);
    updateView();
}

void MainWindow::onGameLost()
{
    ui->m_view->setDisabled(true);
    statusBar()->showMessage(tr("Unfortunately, you died."), MSG_TIMEOUT);
}

void MainWindow::onGameWon()
{
    statusBar()->showMessage(tr("You won!"), MSG_TIMEOUT);
}

void MainWindow::showPreferences()
{
    qDebug() << "Preferences";
    if (CSettingsDialog::getPreferences(m_width, m_height, m_sheep, this))
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
    ui->m_view->resizeColumnsToContents();
    ui->m_view->resizeRowsToContents();

    int32_t h = ui->m_view->rowHeight(1) * m_model->rowCount() + 2;
    int32_t w = ui->m_view->columnWidth(1) * m_model->columnCount() + 2;
    ui->m_view->setFixedSize(w, h);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void MainWindow::loadSettings()
{
    QSettings settings;
    m_height = settings.value("height", int32_t(DEFAULT_HEIGHT)).toInt();
    m_width  = settings.value("width", int32_t(DEFAULT_WIDTH)).toInt();
    m_sheep  = settings.value("sheep", int32_t(DEFAULT_SHEEP)).toInt();

    qDebug() << "Settings: " << m_height << " " << m_width << " " << m_sheep;
}

void MainWindow::saveSettings()
{
    qDebug() << "Save settings";
    QSettings settings;
    settings.setValue("height", m_height);
    settings.setValue("width", m_width);
    settings.setValue("sheep", m_sheep);
}

