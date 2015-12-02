#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <CFieldDelegate.h>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_model(nullptr),
    m_view(nullptr)
{
    ui->setupUi(this);

    initTable();
    initMenubar();
    initConnections();

    setWindowIcon(QIcon(QPixmap(":/images/images/big_sheep.png")));
    setWindowTitle(tr(APP_NAME()));
    resize(290, 340);
    // FIXME: set proper window size
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTable()
{
    m_model = new CTableModel(this);
    m_view  = new CTableView(this);
    m_view->setShowGrid(false);
    m_view->horizontalHeader()->hide();
    m_view->verticalHeader()->hide();
    m_view->horizontalHeader()->setMinimumSectionSize(1);
    m_view->verticalHeader()->setMinimumSectionSize(1);
    m_view->setModel(m_model);
    m_view->setSelectionMode(QAbstractItemView::NoSelection);

    CFieldDelegate *delegate = new CFieldDelegate(this);
    m_view->setItemDelegate(delegate);

    QWidget *centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_view);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
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

void MainWindow::initConnections()
{
    connect(m_view, SIGNAL(clicked(const QModelIndex &)), m_model, SLOT(onTableClicked(const QModelIndex &)));
    connect(m_view, SIGNAL(rightClicked(const QModelIndex&)), m_model, SLOT(onRightClicked(const QModelIndex&)));
    //TODO: connections to Qt5 style
    //TODO: pressed event
}

void MainWindow::newGame()
{
    m_model->newGame();
    m_view->reset();
}

void MainWindow::showAboutBox()
{
    //TODO: credit for icon
    QMessageBox::about(this, tr(APP_NAME()),
        tr("Try to avoid the furious sheep."));
}

void MainWindow::updateView()
{
    m_view->resizeColumnsToContents();
    m_view->resizeRowsToContents();
}
