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
    m_inactiveDelegate(),
    m_translator()
{
    ui->setupUi(this);

    loadSettings();

    initTable();
    initMenubar();
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

    QMenu *languageMenu = new QMenu(tr("&Language"), this);
    QAction *setPlAction = languageMenu->addAction(tr("&Polish"));
    QAction *setEngAction = languageMenu->addAction(tr("&English"));

    menuBar()->addMenu(fileMenu);
    menuBar()->addSeparator();
    menuBar()->addMenu(helpMenu);
    menuBar()->addSeparator();
    menuBar()->addMenu(languageMenu);

    connect(quitAction,         &QAction::triggered, qApp, &QApplication::quit);
    connect(newGameAction,      &QAction::triggered, this, &MainWindow::newGame);
    connect(preferencesAction,  &QAction::triggered, this, &MainWindow::showPreferences);
    connect(aboutAction,        &QAction::triggered, this, &MainWindow::showAboutBox);
//TODO: setting language
//    connect(setPlAction,        &QAction::triggered, this, &MainWindow::setLanguage);
//    connect(setEngAction,       &QAction::triggered, this, &MainWindow::setLanguage);
}

void MainWindow::initTimer()
{
    m_timer.setInterval(1000);
}

void MainWindow::initConnections()
{
    connect(ui->m_view, &CTableView::clicked,       m_model, &CTableModel::onTableClicked);
    connect(ui->m_view, &CTableView::rightClicked,  m_model, &CTableModel::onRightClicked);
    connect(ui->m_view, &CTableView::bothClicked,   m_model, &CTableModel::onBothClicked);

    connect(&m_timer, &QTimer::timeout, this->ui->topWidget, &CTopWidget::incrementTimer);
    connect(m_model, SIGNAL(gameStarted()), &m_timer, SLOT(start()));

    connect(m_model, &CTableModel::sheepDisplay, ui->topWidget, &CTopWidget::setSheepRemainedDisplay);
    //TODO: pressed event

    connect(m_model,        &CTableModel::gameLost,         this, &MainWindow::onGameLost);
    connect(m_model,        &CTableModel::gameWon,          this, &MainWindow::onGameWon);
    connect(ui->topWidget,  &CTopWidget::buttonClicked,     this, &MainWindow::newGame);
}

void MainWindow::newGame()
{
    m_timer.stop();

    m_model->resetModel(m_prefs.height, m_prefs.width, m_prefs.sheep);
    ui->m_view->reset();
    ui->m_view->setModel(m_model);
    ui->m_view->setEnabled(true);
    ui->m_view->setItemDelegate(&m_activeDelegate);
    ui->topWidget->resetTimer();

    ui->topWidget->setDefault();
    statusBar()->showMessage(tr("Good luck!"), MSG_TIMEOUT);
    updateView();
}

void MainWindow::onGameLost()
{
    m_timer.stop();
    statusBar()->showMessage(tr("Unfortunately, you died."), MSG_TIMEOUT);
    ui->m_view->setItemDelegate(&m_inactiveDelegate);
    ui->m_view->setDisabled(true);
    ui->topWidget->setVictory(false);
}

void MainWindow::onGameWon()
{
    m_timer.stop();
    statusBar()->showMessage(tr("You won!"), MSG_TIMEOUT);
    ui->m_view->setItemDelegate(&m_inactiveDelegate);
    ui->m_view->setDisabled(true);
    ui->topWidget->setVictory(true);
}

void MainWindow::showPreferences()
{
    if (CSettingsDialog::getPreferences(m_prefs, this))
    {
        newGame();
    }
}

void MainWindow::setLanguage(const QString langFile)
{
    qDebug() << langFile;

    bool result = m_translator.load(langFile);

    if (!result)
    {
        qWarning("Failed to load the translation file");
    }
    else
    {
        qApp->installTranslator(&m_translator);
        ui->retranslateUi(this);
    }
}

void MainWindow::showAboutBox()
{
    QMessageBox::about(this, APP, tr("Try to avoid the furious sheep.<br>\
                    <div>Icon made by <a href='http://www.freepik.com' title='Freepik'>Freepik</a>\
                    from <a href='http://www.flaticon.com' title='Flaticon'>www.flaticon.com</a>\
                    is licensed under <a href='http://creativecommons.org/licenses/by/3.0/' \
                    title='Creative Commons BY 3.0'>CC BY 3.0</a></div>"));
}

void MainWindow::updateView()
{
    ui->m_view->adjustSizeToContents();
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void MainWindow::loadSettings()
{
    QSettings settings;
    m_prefs.width   = settings.value("width", int32_t(DEFAULT_WIDTH)).toInt();
    m_prefs.height  = settings.value("height", int32_t(DEFAULT_HEIGHT)).toInt();
    m_prefs.sheep   = settings.value("sheep", int32_t(DEFAULT_SHEEP)).toInt();
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("width", m_prefs.width);
    settings.setValue("height", m_prefs.height);
    settings.setValue("sheep", m_prefs.sheep);
}

} // namespace SSw

